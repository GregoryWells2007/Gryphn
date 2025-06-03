#pragma once
#include "gryphn_surface.h"

#ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
        typedef struct gnX11WindowSurfaceInfo_t {
            Display* display;
            Window* window;
        } gnX11WindowSurfaceCreateInfo;

        gnReturnCode gnCreateX11WindowSurface(struct gnWindowSurface_t* windowSurface, gnInstanceHandle instance, struct gnX11WindowSurfaceInfo_t createInfo);
    #endif
    #ifdef GN_WINDOW_WAYLAND
        typedef struct gnWaylandWindowSurfaceInfo_t {
            wl_display* display;
            wl_surface* surface;
        } gnWaylandWindowSurfaceInfo;

        gnReturnCode gnCreateWaylandWindowSurface(struct gnWindowSurface_t* windowSurface, gnInstanceHandle instance, struct gnWaylandWindowSurfaceInfo_t createInfo);
    #endif
#endif


#ifdef GN_PLATFORM_WIN32
    typedef struct gnWin32WindowSurfaceInfo_t {
        HWND* window;
        HINSTANCE* instance;
    } gnWin32WindowSurfaceInfo;

    gnReturnCode gnCreateWin32WindowSurface(struct gnWindowSurface_t* windowSurface, gnInstanceHandle instance, struct gnWin32WindowSurfaceInfo_t createInfo);
#endif

#ifdef GN_PLATFORM_MACOS
    typedef struct gnMacOSWindowSurfaceInfo_t {
        CAMetalLayer* layer;
    } gnMacOSWindowSurfaceInfo;

    gnReturnCode gnCreateMacOSWindowSurface(struct gnWindowSurface_t* windowSurface, gnInstanceHandle instance, struct gnMacOSWindowSurfaceInfo_t createInfo);
#endif
