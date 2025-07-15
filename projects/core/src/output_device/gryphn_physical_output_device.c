#include "gryphn_physical_output_device.h"
#include "instance/gryphn_instance.h"

gnPhysicalOutputDeviceHandle* gnGetPhyscialDevices(gnInstanceHandle instance, uint32_t* count) {
    gnPhysicalOutputDeviceHandle* devices = instance->callingLayer->instanceFunctions._gnGetPhysicalDevices(instance, count);
    for (int i = 0; i < *count; i++)
        devices[i]->instance = instance;
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
    return device->instance->callingLayer->instanceFunctions._gnQueueCanPresentToSurface(device, queueIndex, windowSurface);
}

gnBool gnHasGraphicsQueue(gnPhysicalDevice device) {
    for (int i = 0; i < device->queueProperties.queueCount; i++) {
        if ((device->queueProperties.queueProperties[i].queueType & GN_QUEUE_GRAPHICS) == GN_QUEUE_GRAPHICS) {
            return gnTrue;
        }
    }
    return gnFalse;
}
gnBool gnHasPresentQueue(gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface) {
    for (int i = 0; i < device->queueProperties.queueCount; i++) {
        if (gnQueueCanPresentToSurface(device, i, windowSurface)) {
            return gnTrue;
        }
    }
    return gnFalse;
}

int gnGetGraphicsQueueIndex(gnPhysicalDevice device) {
    for (int i = 0; i < device->queueProperties.queueCount; i++) {
        if ((device->queueProperties.queueProperties[i].queueType & GN_QUEUE_GRAPHICS) == GN_QUEUE_GRAPHICS) {
            return i;
            break;
        }
    }
    return -1;
}
int gnGetPresentQueueIndex(gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface) {
    for (int i = 0; i < device->queueProperties.queueCount; i++) {
        if (gnQueueCanPresentToSurface(device, i, windowSurface)) {
            return i;
            break;
        }
    }
    return -1;
}


gnPhysicalDeviceProperties gnGetPhysicalDeviceProperties(gnPhysicalOutputDeviceHandle device) { return device->properties; }
gnPhysicalDeviceFeatures gnGetPhysicalDeviceFeatures(gnPhysicalOutputDeviceHandle device) { return device->features; }
// gnPhysicalDeviceQueueProperties gnGetPhysicalDeviceQueueProperties(gnPhysicalOutputDeviceHandle device) { return device->queueProperties; }
