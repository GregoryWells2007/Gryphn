#include "opengl_loader.h"
#include "instance/opengl_instance.h"
#include "surface/opengl_surface.h"

gnInstanceFunctions loadOpenGLInstanceFunctions() {
    return (gnInstanceFunctions){
        ._gnCreateInstance = createOpenGLInstance,
        ._gnDestroyInstance = destroyOpenGLInstance,
        // ._gnGetPhysicalDevices = getMetalDevices,
        // ._gnQueueCanPresentToSurface = metalCanQueuePresentToSurface,
        // ._gnCreateOutputDevice = createMetalOutputDevice,
        // ._gnDestroyOutputDevice = destroyMetalOutputDevice,
        #ifdef GN_PLATFORM_LINUX
        #ifdef GN_WINDOW_X11
        ._gnCreateX11WindowSurface = createGLXContext,
        #endif
        #endif
        // ._gnCreateMacOSWindowSurface = createMetalSurface,
        // ._gnDestroyWindowSurface = destroyMetalWindowSurface,
        // ._gnGetSurfaceDetails = getMetalSurfaceDetails
    };
}
