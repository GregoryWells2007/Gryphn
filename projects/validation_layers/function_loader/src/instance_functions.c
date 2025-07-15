#include "instance_functions.h"
#include "../loader_utils.h"
#include <core/src/instance/gryphn_debugger.h>
#include "core/src/output_device/gryphn_output_device.h"
#include "core/src/window_surface/gryphn_surface.h"

gnReturnCode checkCreateInstance(gnInstanceHandle instance, gnInstanceInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(instance, _gnCreateInstance, instanceFunctions, instance, info);
}

void checkDestroyInstance(gnInstance instance) {
    CHECK_VOID_FUNCTION(instance, _gnDestroyInstance, instanceFunctions, instance);
}

gnPhysicalDevice* checkGetPhysicalDevices(gnInstanceHandle instance, uint32_t* count) {
    CHECK_RETURNED_FUNCTION(instance, _gnGetPhysicalDevices, instanceFunctions, NULL, instance, count);
}
gnBool checkQueueCanPresentToSurface(const gnPhysicalDevice device, uint32_t queueIndex, const gnWindowSurfaceHandle windowSurface) {
    CHECK_RETURNED_FUNCTION(device.instance, _gnQueueCanPresentToSurface, instanceFunctions, gnFalse, device, queueIndex, windowSurface);
}

gnReturnCode checkCreateOutputDevice(gnOutputDeviceHandle device, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo) {
    CHECK_FUNCTION_WITH_RETURN_CODE(instance, _gnCreateOutputDevice, instanceFunctions, device, instance, deviceInfo);
}
void checkDestroyOutputDevice(gnOutputDeviceHandle device) {
    CHECK_VOID_FUNCTION(device->instance, _gnDestroyOutputDevice, instanceFunctions, device);
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
