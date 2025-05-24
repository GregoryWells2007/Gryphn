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
        gnDebuggerSetErrorMessage(device.instance->debugger,
            (gnMessageData){
                .message = gnCreateString("gnQueueCanPresentToSurface queue index passed in is large then queueProperties.queueCount")
            }
        );
        return gnFalse;
    }
    return device.instance->functions->_gnQueueCanPresentToSurface(device, queueIndex, windowSurface);
}

int gnGetGraphicsQueueIndex(const struct gnPhysicalDevice_t device) {
    for (int i = 0; i < device.queueProperties.queueCount; i++) {
        if (device.queueProperties.queueProperties[i].queueType & GN_QUEUE_GRAPHICS) {
            return i;
            break;
        }
    }
    gnDebuggerSetErrorMessage(device.instance->debugger,
        (gnMessageData){
            .message = gnCreateString("gnGetGraphicsQueueIndex failed no queue that support graphics on this device")
        }
    );
    return -1;
}
int gnGetPresentQueueIndex(const struct gnPhysicalDevice_t device, struct gnWindowSurface_t windowSurface) {
    for (int i = 0; i < device.queueProperties.queueCount; i++) {
        if (gnQueueCanPresentToSurface(device, i, windowSurface)) {
            return i;
            break;
        }
    }
    gnDebuggerSetErrorMessage(device.instance->debugger,
        (gnMessageData){
            .message = gnCreateString("gnGetPresentQueueIndex failed no queue that support presenting to this window surface")
        }
    );
    return -1;
}
