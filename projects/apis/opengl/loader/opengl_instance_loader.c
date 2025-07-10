#include "opengl_loader.h"
#include "instance/opengl_instance.h"

gnInstanceFunctions loadOpenGLInstanceFunctions() {
    return (gnInstanceFunctions){
        ._gnCreateInstance = createOpenGLInstance,
        ._gnDestroyInstance = destroyOpenGLInstance,
        // ._gnGetPhysicalDevices = getMetalDevices,
        // ._gnQueueCanPresentToSurface = metalCanQueuePresentToSurface,
        // ._gnCreateOutputDevice = createMetalOutputDevice,
        // ._gnDestroyOutputDevice = destroyMetalOutputDevice,
        // ._gnCreateMacOSWindowSurface = createMetalSurface,
        // ._gnDestroyWindowSurface = destroyMetalWindowSurface,
        // ._gnGetSurfaceDetails = getMetalSurfaceDetails
    };
}
