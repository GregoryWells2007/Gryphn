#include "vulkan_loader.h"
#include <instance/vulkan_instance.h>
#include <output_device/vulkan_physical_device.h>
#include <output_device/vulkan_output_devices.h>
#include <vulkan_surface/vulkan_surface.h>

gryphnInstanceFunctionLayers loadVulkanAPILayer() {
    return (gryphnInstanceFunctionLayers) {
        .createInstance = vulkanCreateInstance,
        .destroyInstance = vulkanDestroyInstance,
        .next = NULL
    };
}

gnInstanceFunctions loadVulkanInstanceFunctions() {
    return (gnInstanceFunctions){

        ._gnGetPhysicalDevices = getPhysicalDevices,
        ._gnPhysicalDeviceCanPresentToSurface = deviceCanPresentToSurface,

        ._gnCreateOutputDevice = createVulkanOutputDevice,
        ._gnDestroyOutputDevice = destroyVulkanOutputDevice,


        #ifdef GN_PLATFORM_LINUX
            #ifdef GN_WINDOW_X11
                ._gnCreateX11WindowSurface = createX11WindowSurface,
            #endif
            #ifdef GN_WINDOW_WAYLAND
                ._gnCreateWaylandWindowSurface,
            #endif
        #endif


        #ifdef GN_PLATFORM_WIN32
            ._gnCreateWin32WindowSurface,
        #endif

        #ifdef GN_PLATFORM_MACOS
            ._gnCreateMacOSWindowSurface = createMacOSWindowSurface,
        #endif

        ._gnDestroyWindowSurface = destroyWindowSurface,
        ._gnGetSurfaceDetails = getSurfaceDetails
    };
}
