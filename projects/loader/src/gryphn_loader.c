#include "gryphn_loader.h"
#include <apis/vulkan/loader/vulkan_loader.h>

gnInstanceFunctions loadInstanceFunctions(loaderInfo info) {
    switch (info.api) {
    case GN_RENDERINGAPI_NONE: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_VULKAN: return loadVulkanInstanceFunctions();

    case GN_RENDERINGAPI_SOFTWARE: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX11: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX12: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_OPENGL: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_METAL: return (gnInstanceFunctions){ NULL };
    }
}

gnDeviceFunctions loadDeviceFunctions(loaderInfo info) {
    switch (info.api) {
    case GN_RENDERINGAPI_NONE: return (gnDeviceFunctions){ NULL };
    case GN_RENDERINGAPI_VULKAN: return loadVulkanDeviceFunctions();

    case GN_RENDERINGAPI_SOFTWARE: return (gnDeviceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX11: return (gnDeviceFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX12: return (gnDeviceFunctions){ NULL };
    case GN_RENDERINGAPI_OPENGL: return (gnDeviceFunctions){ NULL };
    case GN_RENDERINGAPI_METAL: return (gnDeviceFunctions){ NULL };
    }
}

gnCommandFunctions loadCommandFunctions(loaderInfo info) {
    switch (info.api) {
    case GN_RENDERINGAPI_NONE: return (gnCommandFunctions){ NULL };
    case GN_RENDERINGAPI_VULKAN: return loadVulkanCommandFunctions();

    case GN_RENDERINGAPI_SOFTWARE: return (gnCommandFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX11: return (gnCommandFunctions){ NULL };
    case GN_RENDERINGAPI_DIRECTX12: return (gnCommandFunctions){ NULL };
    case GN_RENDERINGAPI_OPENGL: return (gnCommandFunctions){ NULL };
    case GN_RENDERINGAPI_METAL: return (gnCommandFunctions){ NULL };
    }
}
