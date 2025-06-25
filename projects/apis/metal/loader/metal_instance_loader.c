#include "metal_loader.h"

gnInstanceFunctions loadMetalInstanceFunctions() {
    return (gnInstanceFunctions){
        ._gnCreateInstance = NULL,
        ._gnDestroyInstance = NULL,
        ._gnGetPhysicalDevices = NULL,
        ._gnQueueCanPresentToSurface = NULL,
        ._gnCreateOutputDevice = NULL,
        ._gnDestroyOutputDevice = NULL,
        ._gnCreateMacOSWindowSurface = NULL,
        ._gnDestroyWindowSurface = NULL,
        ._gnGetSurfaceDetails = NULL
    };
}
