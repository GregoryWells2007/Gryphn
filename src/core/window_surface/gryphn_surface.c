
#include "gryphn_surface.h"
#include "core/gryphn_platform_functions.h"

#ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
        gnReturnCode gnCreateX11WindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnX11WindowSurfaceInfo_t createInfo) {
            return instance->functions->_gnCreateX11WindowSurface(windowSurface, instance, createInfo);
        }
    #endif
    #ifdef GN_WINDOW_WAYLAND
        gnReturnCode gnCreateWaylandWindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnWaylandWindowSurfaceInfo_t createInfo) {
            return instance->functions->_gnCreateWaylandWindowSurface(windowSurface, instance, createInfo);
        }
    #endif
#endif


#ifdef GN_PLATFORM_WIN32
    gnReturnCode gnCreateWin32WindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnWin32WindowSurfaceInfo_t createInfo) {
        return instance->functions->_gnCreateWin32WindowSurface(windowSurface, instance, createInfo);
    }
#endif

#ifdef GN_PLATFORM_MACOS
    gnReturnCode gnCreateMacOSWindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnMacOSWindowSurfaceInfo_t createInfo) {
        windowSurface->instance = instance;
        return instance->functions->_gnCreateMacOSWindowSurface(windowSurface, instance, createInfo);
    }
#endif

void gnDestroyWindowSurface(struct gnWindowSurface_t *windowSurface) {
    windowSurface->instance->functions->_gnDestroyWindowSurface(windowSurface);
}

struct gnSurfaceFormat_t* gnGetSupportedSurfaceFormats(
    struct gnWindowSurface_t* windowSurface,
    struct gnPhysicalDevice_t device,
    uint32_t* formatCount
) {
    return windowSurface->instance->functions->_gnGetSupportedSurfaceFormats(windowSurface, device, formatCount);
}
