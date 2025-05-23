#pragma once
#include <core/instance/gryphn_instance.h>
#include <platform/gryphn_platform_include.h>

struct gnPlatformWindowSurface_t;

typedef struct gnWindowSurface_t {
    struct gnPlatformWindowSurface_t* windowSurface;
    gnInstance* instance;
} gnWindowSurface;
void gnDestroyWindowSurface(struct gnWindowSurface_t* windowSurface);

#ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
        typedef struct gnX11WindowSurfaceInfo_t {
            Display* display;
            Window* window;
        } gnX11WindowSurfaceCreateInfo;

        gnReturnCode gnCreateX11WindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnX11WindowSurfaceInfo_t createInfo);
    #endif
    #ifdef GN_WINDOW_WAYLAND
        typedef struct gnWaylandWindowSurfaceInfo_t {
            wl_display* display;
            wl_surface* surface;
        } gnWaylandWindowSurfaceInfo;

        gnReturnCode gnCreateWaylandWindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnWaylandWindowSurfaceInfo_t createInfo);
    #endif
#endif


#ifdef GN_PLATFORM_WIN32
    typedef struct gnWin32WindowSurfaceInfo_t {
        HWND* window;
        HINSTANCE* instance;
    } gnWin32WindowSurfaceInfo;

    gnReturnCode gnCreateWin32WindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnWin32WindowSurfaceInfo_t createInfo);
#endif

#ifdef GN_PLATFORM_MACOS
    typedef struct gnMacOSWindowSurfaceInfo_t {
        NSWindow* window;
    } gnMacOSWindowSurfaceInfo;

    gnReturnCode gnCreateMacOSWindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnMacOSWindowSurfaceInfo_t createInfo);
#endif
