#include "function_loader.h"
#include "instance_functions.h"

gnInstanceFunctions loadFunctionLoaderInstanceFunctions() {
    return (gnInstanceFunctions){
        ._gnCreateInstance = checkCreateInstance,
        ._gnDestroyInstance = checkDestroyInstance,

        ._gnGetPhysicalDevices = checkGetPhysicalDevices,
        ._gnQueueCanPresentToSurface = checkQueueCanPresentToSurface,

        ._gnCreateOutputDevice = checkCreateOutputDevice,
        ._gnDestroyOutputDevice = checkDestroyOutputDevice,


        #ifdef GN_PLATFORM_LINUX
            #ifdef GN_WINDOW_X11
                ._gnCreateX11WindowSurface = checkCreateX11WindowSurface,
            #endif
            #ifdef GN_WINDOW_WAYLAND
                ._gnCreateWaylandWindowSurface,
            #endif
        #endif


        #ifdef GN_PLATFORM_WIN32
            ._gnCreateWin32WindowSurface,
        #endif

        #ifdef GN_PLATFORM_MACOS
            ._gnCreateMacOSWindowSurface = checkCreateSurfaceMacOS,
        #endif

        ._gnDestroyWindowSurface = checkDestroyWindowSurface,
        ._gnGetSurfaceDetails = checkGetSurfaceDetails
    };
}
gnDeviceFunctions loadFunctionLoaderDeviceFunctions() {
    return (gnDeviceFunctions){
        NULL
    };
}
gnCommandFunctions loadFunctionLoaderCommandFunctions() {
    return (gnCommandFunctions){
        NULL
    };
}
