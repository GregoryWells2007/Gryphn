#ifdef GN_PLATFORM_LINUX
#include "gryphn_platform_linux.h"
#include "gryphn_rendering_api.h"

gnRenderingAPI renderingAPIs[2] = {
    GN_RENDERINGAPI_VULKAN,
    GN_RENDERINGAPI_SOFTWARE
};

gnRenderingAPI* gnGetSupportedRenderingAPIs(int* count) {
    *count = 2;
    return renderingAPIs;
}

#endif
