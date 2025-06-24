#include "gryphn_surface_create_functions.h"
#include "instance/gryphn_instance.h"
#include "gryphn_platform_functions.h"

#ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
        gnReturnCode gnCreateX11WindowSurface(gnWindowSurfaceHandle* windowSurface, gnInstanceHandle instance, gnX11WindowSurfaceInfo createInfo) {
            *windowSurface = malloc(sizeof(struct gnWindowSurface_t));
            (*windowSurface)->instance = instance;
            return instance->functions->_gnCreateX11WindowSurface(*windowSurface, instance, createInfo);
        }
    #endif
    #ifdef GN_WINDOW_WAYLAND
        gnReturnCode gnCreateWaylandWindowSurface(gnWindowSurfaceHandle* windowSurface, gnInstanceHandle instance, struct gnWaylandWindowSurfaceInfo_t createInfo) {
            *windowSurface = malloc(sizeof(struct gnWindowSurface_t));
            return instance->functions->_gnCreateWaylandWindowSurface(windowSurface, instance, createInfo);
        }
    #endif
#endif


#ifdef GN_PLATFORM_WIN32
    gnReturnCode gnCreateWin32WindowSurface(gnWindowSurfaceHandle* windowSurface, gnInstanceHandle instance, struct gnWin32WindowSurfaceInfo_t createInfo) {
        *windowSurface = malloc(sizeof(struct gnWindowSurface_t));
        return instance->functions->_gnCreateWin32WindowSurface(windowSurface, instance, createInfo);
    }
#endif

#ifdef GN_PLATFORM_MACOS
    gnReturnCode gnCreateMacOSWindowSurface(gnWindowSurfaceHandle* windowSurface, gnInstanceHandle instance, struct gnMacOSWindowSurfaceInfo_t createInfo) {
        *windowSurface = malloc(sizeof(struct gnWindowSurface_t));
        (*windowSurface)->instance = instance;
        return instance->functions->_gnCreateMacOSWindowSurface(*windowSurface, instance, createInfo);
    }
#endif
