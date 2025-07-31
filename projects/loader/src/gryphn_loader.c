#include "gryphn_loader.h"
#include <validation_layers/function_loader/loader/function_loader.h>
#ifdef GN_API_VULKAN
#include <apis/vulkan/loader/vulkan_loader.h>
#endif
#ifdef GN_API_METAL
#include <apis/metal/loader/metal_loader.h>
#endif
#ifdef GN_API_OPENGL
#include <apis/opengl/loader/opengl_loader.h>
#endif

#include "stdio.h"
#include "core/src/instance/gryphn_instance.h"

// load the speedy API functions or something like that
dispatcher_bool loadAPIInstanceFunctions(dispatcher_layer* layer) {
    gnRenderingAPI api = *(gnRenderingAPI*)layer->userData;
    gnInstanceFunctions* funcs = (gnInstanceFunctions*)layer->function_array;
    switch (api) {
    case GN_RENDERINGAPI_NONE: *funcs = (gnInstanceFunctions){ NULL };
#ifdef GN_API_VULKAN
    case GN_RENDERINGAPI_VULKAN: *funcs = loadVulkanInstanceFunctions();
#endif

    case GN_RENDERINGAPI_SOFTWARE: *funcs = (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX11: *funcs = (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX12: *funcs = (gnInstanceFunctions){ NULL };
#ifdef GN_API_OPENGL
    case GN_RENDERINGAPI_OPENGL: *funcs = loadOpenGLInstanceFunctions();
#endif
#ifdef GN_API_METAL
    case GN_RENDERINGAPI_METAL: *funcs = loadMetalInstanceFunctions();
#endif
    default: *funcs = (gnInstanceFunctions){NULL};
    }
    return dispatcher_true;
}

gnDeviceFunctions loadAPIDeviceFunctions(gnRenderingAPI api) {
    switch (api) {
    case GN_RENDERINGAPI_NONE: return (gnDeviceFunctions){ NULL };
#ifdef GN_API_VULKAN
    case GN_RENDERINGAPI_VULKAN: return loadVulkanDeviceFunctions();
#endif

    case GN_RENDERINGAPI_SOFTWARE: return (gnDeviceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX11: return (gnDeviceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX12: return (gnDeviceFunctions){ NULL };
#ifdef GN_API_OPENGL
    case GN_RENDERINGAPI_OPENGL: return loadOpenGLDeviceFunctions();
#endif
#ifdef GN_API_METAL
    case GN_RENDERINGAPI_METAL: return loadMetalDeviceFunctions();
#endif

    default: return (gnDeviceFunctions){NULL};
    }
}

gnCommandFunctions loadAPICommandFunctions(gnRenderingAPI api) {
    switch (api) {
    case GN_RENDERINGAPI_NONE: return (gnCommandFunctions){ NULL };
#ifdef GN_API_VULKAN
    case GN_RENDERINGAPI_VULKAN: return loadVulkanCommandFunctions();
#endif

    case GN_RENDERINGAPI_SOFTWARE: return (gnCommandFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX11: return (gnCommandFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX12: return (gnCommandFunctions){ NULL };
    case GN_RENDERINGAPI_OPENGL: return (gnCommandFunctions){ NULL };
#ifdef GN_API_METAL
    case GN_RENDERINGAPI_METAL: return loadMetalCommandFunctions();
#endif

    default: return (gnCommandFunctions){NULL};
    }
}

gnSyncExtFunctions loadAPISyncFunctions(gnRenderingAPI api) {
    switch (api) {
    case GN_RENDERINGAPI_NONE: return (gnSyncExtFunctions){ NULL };
#ifdef GN_API_VULKAN
    case GN_RENDERINGAPI_VULKAN: return loadVulkanSyncFunctions();
#endif

    case GN_RENDERINGAPI_SOFTWARE: return (gnSyncExtFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX11: return (gnSyncExtFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX12: return (gnSyncExtFunctions){ NULL };
    case GN_RENDERINGAPI_OPENGL: return (gnSyncExtFunctions){ NULL };
#ifdef GN_API_METAL
    case GN_RENDERINGAPI_METAL: return loadMetalSyncFunctions();
#endif

    default: return (gnSyncExtFunctions){NULL};
    }
}

gnQueueExtFunctions loadAPIQueueFunctions(gnRenderingAPI api) {
    switch (api) {
    case GN_RENDERINGAPI_NONE: return (gnQueueExtFunctions){ NULL };
#ifdef GN_API_VULKAN
    case GN_RENDERINGAPI_VULKAN: return loadVulkanQueueFunctions();
#endif
    case GN_RENDERINGAPI_SOFTWARE: return (gnQueueExtFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX11: return (gnQueueExtFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX12: return (gnQueueExtFunctions){ NULL };
    case GN_RENDERINGAPI_OPENGL: return (gnQueueExtFunctions){ NULL };
#ifdef GN_API_METAL
    case GN_RENDERINGAPI_METAL: return (gnQueueExtFunctions){ NULL };
#endif

    default: return (gnQueueExtFunctions){NULL};
    }
}

loaderLayer null_layer() {
    return (loaderLayer){
        .deviceFunctions = (gnDeviceFunctions){ NULL },
        .commandFunctions = (gnCommandFunctions){ NULL }
    };
}

loaderLayer api_loaded_layer(gnRenderingAPI api) {
    return (loaderLayer){
        .deviceFunctions = loadAPIDeviceFunctions(api),
        .commandFunctions = loadAPICommandFunctions(api),
    };
}

loaderLayer function_check_layer() {
    return (loaderLayer){
        .deviceFunctions = loadFunctionLoaderDeviceFunctions(),
        .commandFunctions = loadFunctionLoaderCommandFunctions(),

        .syncFunctions = loadFunctionLoaderSyncExtFunctions(),
        .queueFunctions = loadFunctionLoaderQueueExtFunctions(),
    };
}

loaderLayer loadLayer(loaderInfo info) {
    if (info.layerToLoad == api_layer) return api_loaded_layer(info.api);
    if (info.layerToLoad == function_checker_layer) return function_check_layer();
    return null_layer();
}

loaderLayer* loaderGetNextLayer(gnInstance instance) {
    instance->currentLayer--;
    uint32_t nextLayer = instance->currentLayer;
    if (instance->currentLayer == 0) {
        nextLayer = 0;
        resetLayer(instance);
    }
    return &instance->layers.data[nextLayer];
}

void resetLayer(gnInstance instance) {
    instance->currentLayer = (instance->layers.count - 1);
}
