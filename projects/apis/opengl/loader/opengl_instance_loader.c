#include "opengl_loader.h"
#include "instance/opengl_instance.h"
#include "surface/opengl_surface.h"
#include "device/opengl_physical_device.h"
#include "device/opengl_output_device.h"

gryphnInstanceFunctionLayers loadOpenGLAPILayer() {
    return (gryphnInstanceFunctionLayers) {
        .createInstance = openglCreateInstance,
        .destroyInstance = openglDestroyInstance,
        NULL
    };
}

gnInstanceFunctions loadOpenGLInstanceFunctions() {
    return (gnInstanceFunctions){
        ._gnGetPhysicalDevices = getOpenGLDevice,
        ._gnPhysicalDeviceCanPresentToSurface = openglCanDevicePresent,
        ._gnCreateOutputDevice = createOpenGLOutputDevice,
        ._gnDestroyOutputDevice = destroyOpenGLOutputDevice,
        #ifdef GN_PLATFORM_LINUX
        #ifdef GN_WINDOW_X11
        ._gnCreateX11WindowSurface = createGLXContext,
        #endif
        #endif
        ._gnDestroyWindowSurface = destroyOpenGLSurface,
        ._gnGetSurfaceDetails = genOpenGLSurfaceDetails
    };
}
