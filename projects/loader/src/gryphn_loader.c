#include "gryphn_loader.h"
#include <validation_layers/function_loader/loader/function_loader.h>
#ifdef GN_API_VULKAN
#include <apis/vulkan/loader/vulkan_loader.h>
#endif
#ifdef GN_API_METAL
#include <apis/metal/loader/metal_loader.h>
#endif

// load the speedy API functions or something like that
gnInstanceFunctions loadAPIInstanceFunctions(gnRenderingAPI api) {
    switch (api) {
    case GN_RENDERINGAPI_NONE: return (gnInstanceFunctions){ NULL };
#ifdef GN_API_VULKAN
    case GN_RENDERINGAPI_VULKAN: return loadVulkanInstanceFunctions();
#endif

    case GN_RENDERINGAPI_SOFTWARE: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX11: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX12: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_OPENGL: return (gnInstanceFunctions){ NULL };
#ifdef GN_API_METAL
    case GN_RENDERINGAPI_METAL: return loadMetalInstanceFunctions();
#endif
    default: return (gnInstanceFunctions){NULL};
    }
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
    case GN_RENDERINGAPI_OPENGL: return (gnDeviceFunctions){ NULL };
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

loaderLayer null_layer() {
    return (loaderLayer){
        .instanceFunctions = (gnInstanceFunctions){ NULL },
        .deviceFunctions = (gnDeviceFunctions){ NULL },
        .commandFunctions = (gnCommandFunctions){ NULL }
    };
}

loaderLayer api_loaded_layer(gnRenderingAPI api) {
    return (loaderLayer){
        .instanceFunctions = loadAPIInstanceFunctions(api),
        .deviceFunctions = loadAPIDeviceFunctions(api),
        .commandFunctions = loadAPICommandFunctions(api)
    };
}

loaderLayer loadLayer(loaderInfo info) {
    if (info.layerToLoad == no_layer) return null_layer();
    if (info.layerToLoad == api_layer) return api_loaded_layer(info.api);

    return null_layer();
}
