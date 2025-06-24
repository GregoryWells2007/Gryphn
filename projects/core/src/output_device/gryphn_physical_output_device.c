#include "gryphn_physical_output_device.h"
#include "instance/gryphn_instance.h"

gnPhysicalDevice* gnGetPhyscialDevices(gnInstanceHandle instance, uint32_t* count) {
    gnPhysicalDevice* devices = instance->instanceFunctions._gnGetPhysicalDevices(instance, count);
    for (int i = 0; i < *count; i++) {
        devices[i].instance = instance;
    }
    return devices;
}

gnBool gnQueueCanPresentToSurface(const gnPhysicalDevice device, uint32_t queueIndex, gnWindowSurfaceHandle windowSurface) {
    // if (queueIndex >= device.queueProperties.queueCount) {
    //     gnDebuggerSetErrorMessage(device.instance->debugger,
    //         (gnMessageData){
    //             .message = gnCreateString("gnQueueCanPresentToSurface queue index passed in is large then queueProperties.queueCount")
    //         }
    //     );
    //     return gnFalse;
    // }
    return device.instance->instanceFunctions._gnQueueCanPresentToSurface(device, queueIndex, windowSurface);
}

gnBool gnHasGraphicsQueue(const gnPhysicalDevice device) {
    for (int i = 0; i < device.queueProperties.queueCount; i++) {
        if (device.queueProperties.queueProperties[i].queueType & GN_QUEUE_GRAPHICS) {
            return gnTrue;
        }
    }
    return gnFalse;
}
gnBool gnHasPresentQueue(const gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface) {
    for (int i = 0; i < device.queueProperties.queueCount; i++) {
        if (gnQueueCanPresentToSurface(device, i, windowSurface)) {
            return gnTrue;
        }
    }
    return gnFalse;
}

int gnGetGraphicsQueueIndex(const gnPhysicalDevice device) {
    for (int i = 0; i < device.queueProperties.queueCount; i++) {
        if (device.queueProperties.queueProperties[i].queueType & GN_QUEUE_GRAPHICS) {
            return i;
            break;
        }
    }
    return -1;
}
int gnGetPresentQueueIndex(const gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface) {
    for (int i = 0; i < device.queueProperties.queueCount; i++) {
        if (gnQueueCanPresentToSurface(device, i, windowSurface)) {
            return i;
            break;
        }
    }
    return -1;
}
