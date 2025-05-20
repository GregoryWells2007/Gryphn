#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/gryphn_rendering_api.h"

struct gnPlatformInstance;
struct gnFunctions_t;
struct gnDynamicLibrary_t;

typedef struct gnInstanceInfo_t {
    gnString  applicationName;
    gnVersion applicationVersion;

    gnString  engineName;
    gnVersion engineVersion;

    gnRenderingAPI renderingAPI;
} gnInstanceInfo;

typedef struct gnInstance_t {
    struct gnPlatformInstance* instance;
    gnBool valid;

    struct gnFunctions_t* functions;
    struct gnDynamicLibrary_t* dynamicLib;
} gnInstance;

gnReturnCode gnCreateInstance(gnInstance* instance, struct gnInstanceInfo_t info);
void gnDestroyInstance(gnInstance* instance);

// // inline gnReturnCode (*gnInstanceSetWindow)(gnInstance& instance, GLFWwindow* window);

// #ifdef GN_PLATFORM_LINUX
//     #ifdef GN_WINDOW_X11
//         inline gnReturnCode (*gnCreateX11WindowSurface)(gnInstance& instance, Display* display, Window* window);
//     #endif
//     #ifdef GN_WINDOW_WAYLAND
//         inline gnReturnCode (*gnCreateWaylandWindowSurface)(gnInstance& instance, wl_display* display, wl_surface* surface);
//     #endif
// #endif


// #ifdef GN_PLATFORM_WIN32
//     inline gnReturnCode (*gnCreateWindowsWindowSurface)(gnInstance& instance, HWND* window, HINSTANCE* instance);
// #endif

// #ifdef GN_PLATFORM_MACOS
//     typedef void* NSWindow;
//     typedef void* NSView;

//     inline gnReturnCode (*gnCreateMacOSWindowSurface)(gnInstance& instance, NSWindow window, NSView view);
// #endif
