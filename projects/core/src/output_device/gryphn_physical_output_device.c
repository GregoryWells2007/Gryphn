#include "gryphn_physical_output_device.h"
#include "instance/gryphn_instance.h"

gnPhysicalOutputDeviceHandle* gnGetPhyscialDevices(gnInstanceHandle instance, uint32_t* count) {
    gnPhysicalOutputDeviceHandle* devices = instance->callingLayer->instanceFunctions._gnGetPhysicalDevices(instance, count);
    for (int i = 0; i < *count; i++)
        devices[i]->instance = instance;
    return devices;
}

gnBool gnPhysicalDeviceCanPresentToSurface(gnPhysicalOutputDeviceHandle device, gnWindowSurfaceHandle windowSurface) {
    return device->instance->callingLayer->instanceFunctions._gnPhysicalDeviceCanPresentToSurface(device, windowSurface);
}

gnPhysicalDeviceProperties gnGetPhysicalDeviceProperties(gnPhysicalOutputDeviceHandle device) { return device->properties; }
gnPhysicalDeviceFeatures gnGetPhysicalDeviceFeatures(gnPhysicalOutputDeviceHandle device) { return device->features; }

// gnBool gnHasGraphicsQueue(gnPhysicalDevice device) {
//     for (int i = 0; i < device->queueProperties.queueCount; i++) {
//         if ((device->queueProperties.queueProperties[i].queueType & GN_QUEUE_GRAPHICS) == GN_QUEUE_GRAPHICS) {
//             return gnTrue;
//         }
//     }
//     return gnFalse;
// }
// gnBool gnHasPresentQueue(gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface) {
//     for (int i = 0; i < device->queueProperties.queueCount; i++) {
//         if (gnQueueCanPresentToSurface(device, i, windowSurface)) {
//             return gnTrue;
//         }
//     }
//     return gnFalse;
// }

// int gnGetGraphicsQueueIndex(gnPhysicalDevice device) {
//     for (int i = 0; i < device->queueProperties.queueCount; i++) {
//         if ((device->queueProperties.queueProperties[i].queueType & GN_QUEUE_GRAPHICS) == GN_QUEUE_GRAPHICS) {
//             return i;
//             break;
//         }
//     }
//     return -1;
// }
// int gnGetPresentQueueIndex(gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface) {
//     for (int i = 0; i < device->queueProperties.queueCount; i++) {
//         if (gnQueueCanPresentToSurface(device, i, windowSurface)) {
//             return i;
//             break;
//         }
//     }
//     return -1;
// }

// gnPhysicalDeviceQueueProperties gnGetPhysicalDeviceQueueProperties(gnPhysicalOutputDeviceHandle device) { return device->queueProperties; }
