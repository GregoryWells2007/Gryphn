#pragma once
#include <gryphn/gryphn_utils.h>
#include "application_information/gryphn_app_info.h"
#include "core/debugger/gryphn_debugger.h"
#include <core/output_device/gryphn_output_device.h>
#include <platform/gryphn_platform_include.h>

struct gnPlatformInstanceData;

struct gnInstance {
ACCESS_LEVEL:
    bool valid = false;
    gnPlatformInstanceData* instance = nullptr;
    gnAppInfo AppInfo;
    gnDebugger* debugger;
public:
    gnInstance() {}
};

void gnInstanceSetAppInfo(gnInstance& instance, const gnAppInfo info);
void gnInstanceSetDebugger(gnInstance& instance, gnDebugger& debugger);

inline gnReturnCode (*gnCreateInstance)(gnInstance* instance);
inline void (*gnDestroyInstance)(gnInstance& instance);
// inline gnReturnCode (*gnInstanceSetWindow)(gnInstance& instance, GLFWwindow* window);

#ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
        inline gnReturnCode (*gnCreateX11WindowSurface)(gnInstance& instance, Display* display, Window* window);
    #endif
    #ifdef GN_WINDOW_WAYLAND
        inline gnReturnCode (*gnCreateWaylandWindowSurface)(gnInstance& instance, wl_display* display, wl_surface* surface);
    #endif
#endif


#ifdef GN_PLATFORM_WIN32
    inline gnReturnCode (*gnCreateWindowsWindowSurface)(gnInstance& instance, HWND* window, HINSTANCE* instance);
#endif

#ifdef GN_PLATFORM_MACOS
    inline gnReturnCode (*gnCreateMacOSWindowSurface)(gnInstance& instance, NS::Window* window, NS::View* view);
#endif


// TODO: if instance creation fails add in a query to why the instance creation failed
// Lowkey thats a lot of work tho and I dont really want to do alllllll that
