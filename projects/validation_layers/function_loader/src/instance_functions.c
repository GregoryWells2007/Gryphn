#include "instance_functions.h"
#include "../loader_utils.h"
#include <core/src/instance/gryphn_debugger.h>
#include "core/src/output_device/gryphn_output_device.h"
#include "core/src/window_surface/gryphn_surface.h"

gnReturnCode checkCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* info, PFN_gnCreateInstance_layer* next) {
    if (next->func == NULL) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load gnCreateInstance this indicates a bug within gryphn")
        });
        return GN_FAILED_TO_LOAD_FUNCTION;
    }
    return (*(PFN_gnCreateInstance*)next->func)(instance, info, next->next);
}

void checkDestroyInstance(gnInstanceHandle instance, PFN_gnDestroyInstance_layer* next) {
    if (next->func == NULL) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load gnDestroyInstance this indicates a bug within gryphn")
        });
    }
    (*(PFN_gnDestroyInstance*)next->func)(instance, next->next);
}

gnPhysicalDevice* checkGetPhysicalDevices(gnInstanceHandle instance, uint32_t* count) {
    CHECK_RETURNED_FUNCTION(instance, _gnGetPhysicalDevices, instanceFunctions, NULL, instance, count);
}
gnBool checkCanDevicePresent(gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface) {
    CHECK_RETURNED_FUNCTION(device->instance, _gnPhysicalDeviceCanPresentToSurface, instanceFunctions, GN_FALSE, device, windowSurface);
}

gnReturnCode checkCreateOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle device, gnOutputDeviceInfo deviceInfo) {
    CHECK_FUNCTION_WITH_RETURN_CODE(instance, _gnCreateOutputDevice, instanceFunctions, instance, device, deviceInfo);
}
void checkDestroyOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle device) {
    CHECK_VOID_FUNCTION(device->instance, _gnDestroyOutputDevice, instanceFunctions, instance, device);
}

#ifdef GN_PLATFORM_MACOS
gnReturnCode checkCreateSurfaceMacOS(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnMacOSWindowSurfaceInfo createInfo) {
    CHECK_FUNCTION_WITH_RETURN_CODE(instance, _gnCreateMacOSWindowSurface, instanceFunctions, windowSurface, instance, createInfo);
}
#endif
#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
gnReturnCode checkCreateX11WindowSurface(gnWindowSurface surface, gnInstance instance, gnX11WindowSurfaceInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(instance, _gnCreateX11WindowSurface, instanceFunctions, surface, instance, info);
}
#endif
#endif

void checkDestroyWindowSurface(gnWindowSurfaceHandle windowSurface) {
    CHECK_VOID_FUNCTION(windowSurface->instance, _gnDestroyWindowSurface, instanceFunctions, windowSurface);
}
gnSurfaceDetails checkGetSurfaceDetails(gnWindowSurfaceHandle windowSurface, gnPhysicalDevice device) {
    CHECK_RETURNED_FUNCTION(windowSurface->instance, _gnGetSurfaceDetails, instanceFunctions, (gnSurfaceDetails){}, windowSurface, device);
}
