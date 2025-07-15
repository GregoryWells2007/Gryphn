#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "utils/gryphn_bool.h"
#include "gryphn_handles.h"

typedef struct gnInstanceInfo gnInstanceInfo;
typedef struct gnSurfaceDetails gnSurfaceDetails;
typedef struct gnOutputDeviceInfo gnOutputDeviceInfo;


#ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
        typedef struct gnX11WindowSurfaceInfo gnX11WindowSurfaceInfo;
    #endif
#endif
#ifdef GN_PLATFORM_MACOS
    typedef struct gnMacOSWindowSurfaceInfo gnMacOSWindowSurfaceInfo;
#endif

typedef struct gnInstanceFunctions {
    gnReturnCode (*_gnCreateInstance)(gnInstanceHandle instance, gnInstanceInfo info);
    void (*_gnDestroyInstance)(gnInstanceHandle instance);

    gnPhysicalDevice* (*_gnGetPhysicalDevices)(gnInstanceHandle instance, uint32_t* count);
    gnBool (*_gnPhysicalDeviceCanPresentToSurface)(gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface);

    gnReturnCode (*_gnCreateOutputDevice)(gnOutputDeviceHandle device, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo);
    void (*_gnDestroyOutputDevice)(gnOutputDeviceHandle device);


    #ifdef GN_PLATFORM_LINUX
        #ifdef GN_WINDOW_X11
            gnReturnCode (*_gnCreateX11WindowSurface)(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnX11WindowSurfaceInfo createInfo);
        #endif
        #ifdef GN_WINDOW_WAYLAND
            gnReturnCode (*_gnCreateWaylandWindowSurface)(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnWaylandWindowSurfaceInfo createInfo);
        #endif
    #endif


    #ifdef GN_PLATFORM_WIN32
        gnReturnCode (*_gnCreateWin32WindowSurface)(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnWin32WindowSurfaceInfo createInfo);
    #endif

    #ifdef GN_PLATFORM_MACOS
        gnReturnCode (*_gnCreateMacOSWindowSurface)(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnMacOSWindowSurfaceInfo createInfo);
    #endif

    void (*_gnDestroyWindowSurface)(gnWindowSurfaceHandle windowSurface);
    gnSurfaceDetails (*_gnGetSurfaceDetails)(gnWindowSurfaceHandle windowSurface, gnPhysicalDevice device);
} gnInstanceFunctions;
