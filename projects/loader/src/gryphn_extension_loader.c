#include "gryphn_extension_loader.h"

#ifdef GN_API_VULKAN
#include <apis/vulkan/loader/vulkan_loader.h>
#endif
#ifdef GN_API_METAL
#include <apis/metal/loader/metal_loader.h>
#endif
#ifdef GN_API_OPENGL
#include <apis/opengl/loader/opengl_loader.h>
#endif

gnBool gnIsExtensionSuppoted(gnRenderingAPI api, gnExtension extension) {
    switch (api) {
    case GN_RENDERINGAPI_NONE: return GN_FALSE;
#ifdef GN_API_VULKAN
    case GN_RENDERINGAPI_VULKAN: return vulkanIsExtensionSupported(extension);
#endif
#ifdef GN_API_SOFTWARE
    case GN_RENDERINGAPI_SOFTWARE: return softwareIsExtensionSupported(extension);
#endif
#ifdef GN_API_DX11
    case GN_RENDERINGAPI_DIRECTX11: return dx11IsExtensionSupported(extension);
#endif
#ifdef GN_API_DX12
    case GN_RENDERINGAPI_DIRECTX12: return dx12IsExtensionSupported(extension);
#endif
#ifdef GN_API_OPENGL
    case GN_RENDERINGAPI_OPENGL: return openglIsExtensionSupported(extension);
#endif
#ifdef GN_API_METAL
    case GN_RENDERINGAPI_METAL: return metalIsExtensionSupported(extension);
#endif
    default: return GN_FALSE;
    }
}
