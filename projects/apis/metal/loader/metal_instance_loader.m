#include "metal_loader.h"
#include "instance/metal_instance.h"
#include "surface/metal_surface.h"
#include "devices/metal_output_devices.h"

gnInstanceFunctions loadMetalInstanceFunctions() {
    return (gnInstanceFunctions){
        ._gnCreateInstance = createMetalInstance,
        ._gnDestroyInstance = destroyMetalInstance,
        ._gnGetPhysicalDevices = getMetalDevices,
        ._gnPhysicalDeviceCanPresentToSurface = metalCanDevicePresent,
        ._gnCreateOutputDevice = createMetalOutputDevice,
        ._gnDestroyOutputDevice = destroyMetalOutputDevice,
        ._gnCreateMacOSWindowSurface = createMetalSurface,
        ._gnDestroyWindowSurface = destroyMetalWindowSurface,
        ._gnGetSurfaceDetails = getMetalSurfaceDetails
    };
}
