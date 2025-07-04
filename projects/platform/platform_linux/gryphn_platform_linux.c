#ifdef GN_PLATFORM_LINUX
#include "gryphn_platform_linux.h"
#include "gryphn_rendering_api.h"

gnRenderingAPI renderingAPIs[3] = {
    GN_RENDERINGAPI_VULKAN,
    GN_RENDERINGAPI_OPENGL,
    GN_RENDERINGAPI_SOFTWARE
};

gnRenderingAPI* gnGetSupportedRenderingAPIs(int* count) {
    *count = 3;
    return renderingAPIs;
}

gnBool gnSupportsRenderingAPI(gnRenderingAPI api) {
    for (int i = 0; i < 3; i++) if (api == renderingAPIs[i]) return gnTrue;
    return gnFalse;
}

#endif
