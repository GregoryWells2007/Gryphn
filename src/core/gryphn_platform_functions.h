#pragma once
// theoretically you could have multible gryphn instances running in one application,
// why I dont know
#include "instance/gryphn_instance.h"
#include "debugger/gryphn_debugger.h"
#include "output_device/gryphn_physical_output_device.h"
#include "output_device/gryphn_output_device.h"
#include "window_surface/gryphn_surface.h"
#include "window_surface/gryphn_surface_create_functions.h"
#include "shader_module/gryphn_shader_module.h"

typedef struct gnFunctions_t {
    gnReturnCode (*_gnCreateInstance)(gnInstance* instance, struct gnInstanceInfo_t info);
    void (*_gnDestroyInstance)(gnInstance* instance);

    gnReturnCode (*_gnCreateDebugger)(gnDebugger* debugger, gnInstance* instance, const struct gnDebuggerInfo_t info);
    void (*_gnDestroyDebugger)(gnDebugger* debugger);

    gnPhysicalDevice* (*_gnGetPhysicalDevices)(gnInstance* instance, uint32_t* count);
    gnBool (*_gnQueueCanPresentToSurface)(const struct gnPhysicalDevice_t device, uint32_t queueIndex, const struct gnWindowSurface_t windowSurface);


    gnReturnCode (*_gnCreateOutputDevoce)(gnOutputDevice* device, gnInstance* instance, struct gnOutputDeviceInfo_t deviceInfo);
    void (*_gnDestroyOutputDevice)(gnOutputDevice* device);



    #ifdef GN_PLATFORM_LINUX
        #ifdef GN_WINDOW_X11
            gnReturnCode (*_gnCreateX11WindowSurface)(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnX11WindowSurfaceInfo_t createInfo);
        #endif
        #ifdef GN_WINDOW_WAYLAND
            gnReturnCode (*_gnCreateWaylandWindowSurface)(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnWaylandWindowSurfaceInfo_t createInfo);
        #endif
    #endif


    #ifdef GN_PLATFORM_WIN32
        gnReturnCode (*_gnCreateWin32WindowSurface)(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnWin32WindowSurfaceInfo_t createInfo);
    #endif

    #ifdef GN_PLATFORM_MACOS
        gnReturnCode (*_gnCreateMacOSWindowSurface)(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnMacOSWindowSurfaceInfo_t createInfo);
    #endif

    void (*_gnDestroyWindowSurface)(struct gnWindowSurface_t* windowSurface);
    struct gnSurfaceDetails_t (*_gnGetSurfaceDetails)(struct gnWindowSurface_t* windowSurface, struct gnPhysicalDevice_t device);
} gnFunctions;

#include "core/presentation_queue/gryphn_presentation_queue.h"
typedef struct gnDeviceFunctions_t {
    gnReturnCode (*_gnCreatePresentationQueue)(gnPresentationQueue* presentationQueue, const gnOutputDevice* device, struct gnPresentationQueueInfo_t presentationInfo);
    void (*_gnDestroyPresentationQueue)(gnPresentationQueue *presentationQueue);

    gnReturnCode (*_gnCreateShaderModule)(struct gnShaderModule_t* module, struct gnOutputDevice_t* device, struct gnShaderModuleInfo_t shaderModuleInfo);
    void (*_gnDestroyShaderModule)(struct gnShaderModule_t* module);
} gnDeviceFunctions;
