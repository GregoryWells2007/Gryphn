#include "gryphn_physical_output_device.h"
#include "core/gryphn_platform_functions.h"
#include "core/window_surface/gryphn_surface.h"
#include "stdio.h"

gnPhysicalDevice* gnGetPhyscialDevices(gnInstance* instance, uint32_t* count) {
    gnPhysicalDevice* devices = instance->functions->_gnGetPhysicalDevices(instance, count);
    for (int i = 0; i < *count; i++) {
        devices[i].instance = instance;
    }
    return devices;
}

gnBool gnQueueCanPresentToSurface(const struct gnPhysicalDevice_t device, uint32_t queueIndex, const struct gnWindowSurface_t windowSurface) {
    if (queueIndex >= device.queueProperties.queueCount) {
        device.instance->debugger->info.callback(
            GN_MESSAGE_ERROR,
            GN_DEBUG_MESSAGE_VALIDATION,
            (gnMessageData){
                .message = gnCreateString("gnQueueCanPresentToSurface queue index passed in is large then queueProperties.queueCount")
            },
            NULL
        );
        return gnFalse;
    }
    return device.instance->functions->_gnQueueCanPresentToSurface(device, queueIndex, windowSurface);
}
