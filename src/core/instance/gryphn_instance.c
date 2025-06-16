#include "gryphn_instance.h"
#include "init/gryphn_init.h"
#include <core/gryphn_platform_functions.h>
#include "core/instance/gryphn_instance.h"
#include "core/debugger/gryphn_debugger.h"
#include "core/gryphn_handles.h"
#include "stdio.h"

#define GN_VALIDATED_FUNCTION(where, func, param_list, args, code) \
code _##func##Fn param_list { \
    if ((where->unvalidatedFunctions)->_##func == NULL) { \
        gnDebuggerSetErrorMessage(where->debugger, (gnMessageData){ \
            "function " #func " was not loaded" \
        }); \
    } \
    return (where->unvalidatedFunctions)->_##func args; \
}

#define GN_VALIDATED_FUNCTION_ERROR_CODE(where, func, param_list, args) \
gnErrorCode _##func##Fn param_list { \
    if ((where->unvalidatedFunctions)->_##func == NULL) { \
        gnDebuggerSetErrorMessage(where->debugger, (gnMessageData){ \
            "function " #func " was not loaded" \
        }); \
        return GN_FAILED_TO_LOAD_FUNCTION; \
    } \
    return (where->unvalidatedFunctions)->_##func args; \
}


#define GN_VALIDATED_FUNCTION_VOID(where, func, param_list, args) \
void _##func##Fn param_list { \
    if ((where->unvalidatedFunctions)->_##func == NULL) { \
        gnDebuggerSetErrorMessage(where->debugger, (gnMessageData){ \
            "function " #func " was not loaded" \
        }); \
        return;\
    } \
    (where->unvalidatedFunctions)->_##func args;\
}

GN_VALIDATED_FUNCTION_ERROR_CODE(instance, gnCreateInstance,
                      (gnInstanceHandle instance, gnInstanceInfo info),
                      (instance, info))
GN_VALIDATED_FUNCTION_VOID(instance, gnDestroyInstance,
                      (gnInstanceHandle instance),
                      (instance))
GN_VALIDATED_FUNCTION(instance, gnGetPhysicalDevices,
                      (gnInstanceHandle instance, uint32_t* count),
                      (instance, count), gnPhysicalDevice*)
GN_VALIDATED_FUNCTION(device.instance, gnQueueCanPresentToSurface,
                    (const gnPhysicalDevice device, uint32_t queueIndex, const gnWindowSurfaceHandle windowSurface),
                    (device, queueIndex, windowSurface), gnBool)
GN_VALIDATED_FUNCTION_ERROR_CODE(device->instance, gnCreateOutputDevice,
                    (gnOutputDeviceHandle device, gnInstanceHandle instance, struct gnOutputDeviceInfo_t deviceInfo),
                    (device, instance, deviceInfo))
GN_VALIDATED_FUNCTION_VOID(device->instance, gnDestroyOutputDevice,
                      (gnOutputDeviceHandle device),
                      (device))


#ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
        GN_VALIDATED_FUNCTION_ERROR_CODE(instance, gnCreateX11WindowSurface,
                            (gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnX11WindowSurfaceInfo createInfo),
                            (windowSurface, instance, createInfo))
    #endif
    #ifdef GN_WINDOW_WAYLAND
        GN_VALIDATED_FUNCTION_ERROR_CODE(instance, gnCreateWaylandWindowSurface,
                            (gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnWaylandWindowSurfaceInfo createInfo),
                            (windowSurface, instance, createInfo))
    #endif
#endif

#ifdef GN_PLATFORM_WIN32
    GN_VALIDATED_FUNCTION_ERROR_CODE(instance, gnCreateWin32WindowSurface,
                        (gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnWin32WindowSurfaceInfo createInfo),
                        (windowSurface, instance, createInfo))
#endif

#ifdef GN_PLATFORM_MACOS
    GN_VALIDATED_FUNCTION_ERROR_CODE(instance, gnCreateMacOSWindowSurface,
                        (gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnMacOSWindowSurfaceInfo createInfo),
                        (windowSurface, instance, createInfo))
#endif

GN_VALIDATED_FUNCTION_VOID(windowSurface->instance, gnDestroyWindowSurface,
                      (gnWindowSurfaceHandle windowSurface),
                      (windowSurface))

GN_VALIDATED_FUNCTION(windowSurface->instance, gnGetSurfaceDetails,
                    (gnWindowSurfaceHandle windowSurface, gnPhysicalDevice device),
                    (windowSurface, device), gnSurfaceDetails)



gnReturnCode gnCreateInstance(gnInstanceHandle* instanceHandlePtr, gnInstanceInfo info) {
    *instanceHandlePtr = malloc(sizeof(struct gnInstance_t));
    gnInstanceHandle instance = *instanceHandlePtr;
    instance->debugger = NULL;

    if (!gnIsAPISupported(info.renderingAPI)) return GN_UNSUPPORTED_RENDERING_API;
    instance->loadDeviceFunctions = gnFalse;
    instance->debugger = NULL;
    instance->dynamicLib = gnLoadRenderingDLL(info.renderingAPI);
    if (instance->dynamicLib == NULL) return GN_UNABLE_TO_LOAD_DYNAMIC_LIBARRY;
    instance->functions = gnLoadFunctions(instance);

    gnBool validateFunctions = gnFalse;
    for (int i = 0; i < info.debugger->info.layerCount; i++)
        if (info.debugger->info.layers[i] == GN_DEBUGGER_LAYER_FUNCTIONS) validateFunctions = gnTrue;

    if (validateFunctions) {
        instance->functions->_gnCreateInstance = _gnCreateInstanceFn;
        instance->functions->_gnDestroyInstance = _gnDestroyInstanceFn;
        instance->functions->_gnGetPhysicalDevices = _gnGetPhysicalDevicesFn;
        instance->functions->_gnQueueCanPresentToSurface = _gnQueueCanPresentToSurfaceFn;
        instance->functions->_gnCreateOutputDevice = _gnCreateOutputDeviceFn;
        instance->functions->_gnDestroyOutputDevice = _gnDestroyOutputDeviceFn;

        #ifdef GN_PLATFORM_LINUX
            #ifdef GN_WINDOW_X11
                instance->functions->_gnCreateX11WindowSurface = _gnCreateX11WindowSurfaceFn;
            #endif
            #ifdef GN_WINDOW_WAYLAND
                instance->functions->_gnCreateWaylandWindowSurface = _gnCreateWaylandWindowSurfaceFn;
            #endif
        #endif

        #ifdef GN_PLATFORM_WIN32
            instance->functions->_gnCreateWaylandWindowSurface = _gnCreateWaylandWindowSurfaceFn;
        #endif

        #ifdef GN_PLATFORM_MACOS
            instance->functions->_gnCreateMacOSWindowSurface = _gnCreateMacOSWindowSurfaceFn;
        #endif
        instance->functions->_gnDestroyWindowSurface = _gnDestroyWindowSurfaceFn;
        instance->functions->_gnGetSurfaceDetails = _gnGetSurfaceDetailsFn;

        instance->unvalidatedFunctions = gnLoadFunctions(instance);
    }

    instance->loadCommandFunctions = gnFalse;
    instance->loadDeviceFunctions = gnFalse;
    instance->debugger = info.debugger;
    return instance->functions->_gnCreateInstance(instance, info);
}

void gnDestroyInstance(gnInstanceHandle instance) {
    instance->functions->_gnDestroyInstance(instance);
}
