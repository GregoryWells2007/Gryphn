#include <output_device/gryphn_physical_output_device.h>
#include <Metal/Metal.h>
#include "metal_output_devices.h"
#include "window_surface/gryphn_surface.h"

gnPhysicalDevice* getMetalDevices(gnInstanceHandle instance, uint32_t* deviceCount) {
    NSArray *devices = MTLCopyAllDevices();
    *deviceCount = [devices count];
    gnPhysicalDevice* devicesList = (gnPhysicalDevice*)malloc(sizeof(gnPhysicalDevice) * *deviceCount);
    for (int i = 0; i < *deviceCount; i++) {
        devicesList[i].physicalDevice = malloc(sizeof(gnPlatformPhysicalDevice));
        devicesList[i].physicalDevice->device = [devices objectAtIndex:0];


        id<MTLDevice> device = [devices objectAtIndex:0];
        devicesList[i].properties.name = gnCreateString([[device name] cStringUsingEncoding:NSUTF8StringEncoding]);
        MTLDeviceLocation deviceLocation = device.locationNumber;
        if (deviceLocation == MTLDeviceLocationBuiltIn)
            devicesList[i].properties.deviceType = GN_INTEGRATED_DEVICE;
        else if (deviceLocation == MTLDeviceLocationSlot)
            devicesList[i].properties.deviceType = GN_DEDICATED_DEVICE;
        else if (deviceLocation == MTLDeviceLocationExternal)
            devicesList[i].properties.deviceType = GN_EXTERNAL_DEVICE;

        // below I am going to fake that there is one queue that can support graphics, compute, and transfer queues
        devicesList[i].queueProperties.queueCount = 1;
        devicesList[i].queueProperties.queueProperties = malloc(sizeof(gnQueueProperties));
        devicesList[i].queueProperties.queueProperties[0] = (gnQueueProperties){
            .queueCount = 1,
            .queueType = GN_QUEUE_GRAPHICS | GN_QUEUE_COMPUTE | GN_QUEUE_TRANSFER
        };
    }
    [devices release];
    return devicesList;
}

gnBool metalCanQueuePresentToSurface(const gnPhysicalDevice device, uint32_t queueIndex, gnWindowSurface windowSurface) {
    return gnTrue; // I belive that a window should always be able to present to a surface in metal
}
