#include "gryphn_loader.h"
#ifdef GN_API_VULKAN
#include <apis/vulkan/loader/vulkan_loader.h>
#endif
#ifdef GN_API_METAL
#include <apis/metal/loader/metal_loader.h>
#endif

gnInstanceFunctions loadInstanceFunctions(loaderInfo info) {
    switch (info.api) {
    case GN_RENDERINGAPI_NONE: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_VULKAN: return loadVulkanInstanceFunctions(info);

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

gnDeviceFunctions loadDeviceFunctions(loaderInfo info) {
    switch (info.api) {
    case GN_RENDERINGAPI_NONE: return (gnDeviceFunctions){ NULL };
    case GN_RENDERINGAPI_VULKAN: return loadVulkanDeviceFunctions(info);

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

gnCommandFunctions loadCommandFunctions(loaderInfo info) {
    switch (info.api) {
    case GN_RENDERINGAPI_NONE: return (gnCommandFunctions){ NULL };
    case GN_RENDERINGAPI_VULKAN: return loadVulkanCommandFunctions(info);

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
