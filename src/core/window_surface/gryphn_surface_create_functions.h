#pragma once
#include <platform/gryphn_platform_include.h>
#include "core/gryphn_handles.h"
#include "utils/gryphn_error_code.h"

#ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
        typedef struct gnX11WindowSurfaceInfo_t {
            Display* display;
            Window window;
        } gnX11WindowSurfaceInfo;

        gnReturnCode gnCreateX11WindowSurface(gnWindowSurfaceHandle* windowSurface, gnInstanceHandle instance, gnX11WindowSurfaceInfo createInfo);
    #endif
    #ifdef GN_WINDOW_WAYLAND
        typedef struct gnWaylandWindowSurfaceInfo_t {
            wl_display* display;
            wl_surface* surface;
        } gnWaylandWindowSurfaceInfo;

        gnReturnCode gnCreateWaylandWindowSurface(gnWindowSurfaceHandle* windowSurface, gnInstanceHandle instance, struct gnWaylandWindowSurfaceInfo_t createInfo);
    #endif
#endif


#ifdef GN_PLATFORM_WIN32
    typedef struct gnWin32WindowSurfaceInfo_t {
        HWND* window;
        HINSTANCE* instance;
    } gnWin32WindowSurfaceInfo;

    gnReturnCode gnCreateWin32WindowSurface(gnWindowSurfaceHandle* windowSurface, gnInstanceHandle instance, struct gnWin32WindowSurfaceInfo_t createInfo);
#endif

#ifdef GN_PLATFORM_MACOS
    typedef struct gnMacOSWindowSurfaceInfo_t {
        CAMetalLayer* layer;
    } gnMacOSWindowSurfaceInfo;

    gnReturnCode gnCreateMacOSWindowSurface(gnWindowSurfaceHandle* windowSurface, gnInstanceHandle instance, struct gnMacOSWindowSurfaceInfo_t createInfo);
#endif
