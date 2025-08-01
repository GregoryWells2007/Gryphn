#include <output_device/gryphn_physical_output_device.h>
#include <Metal/Metal.h>
#include "metal_output_devices.h"
#include "window_surface/gryphn_surface.h"

gnPhysicalDevice* getMetalDevices(gnInstanceHandle instance, uint32_t* deviceCount) {
    NSArray *devices = MTLCopyAllDevices();
    *deviceCount = (uint32_t)[devices count];
    gnPhysicalDevice* devicesList = (gnPhysicalDevice*)malloc(sizeof(gnPhysicalDevice) * *deviceCount);
    for (int i = 0; i < *deviceCount; i++) {
        devicesList[i] = malloc(sizeof(gnPhysicalOutputDevice_t));
        devicesList[i]->physicalDevice = malloc(sizeof(gnPlatformPhysicalDevice));
        devicesList[i]->physicalDevice->device = [devices objectAtIndex:0];


        id<MTLDevice> device = [devices objectAtIndex:0];
        devicesList[i]->properties.name = gnCreateString([[device name] cStringUsingEncoding:NSUTF8StringEncoding]);
        MTLDeviceLocation deviceLocation = device.locationNumber;
        if (deviceLocation == MTLDeviceLocationBuiltIn)
            devicesList[i]->properties.deviceType = GN_INTEGRATED_DEVICE;
        else if (deviceLocation == MTLDeviceLocationSlot)
            devicesList[i]->properties.deviceType = GN_DEDICATED_DEVICE;
        else if (deviceLocation == MTLDeviceLocationExternal)
            devicesList[i]->properties.deviceType = GN_EXTERNAL_DEVICE;

        devicesList[i]->features.maxColorSamples = GN_SAMPLE_BIT_1;
        if ([device supportsTextureSampleCount:2]) { devicesList[i]->features.maxColorSamples |= GN_SAMPLE_BIT_2; } else {}
        if ([device supportsTextureSampleCount:4]) { devicesList[i]->features.maxColorSamples |= GN_SAMPLE_BIT_4; } else {}
        if ([device supportsTextureSampleCount:8]) { devicesList[i]->features.maxColorSamples |= GN_SAMPLE_BIT_8; } else {}
        if ([device supportsTextureSampleCount:16]) { devicesList[i]->features.maxColorSamples |= GN_SAMPLE_BIT_16; } else {}
        if ([device supportsTextureSampleCount:32]) { devicesList[i]->features.maxColorSamples |= GN_SAMPLE_BIT_32; } else {}
        devicesList[i]->features.maxDepthSamples = devicesList[i]->features.maxColorSamples;

        devicesList[i]->features.maxMemoryAllocations = 0x40000000;
        devicesList[i]->features.maxPushConstantSize = 4096;
    }
    [devices release];
    return devicesList;
}

gnBool metalCanDevicePresent(gnPhysicalDevice device, gnWindowSurface windowSurface) {
    return GN_TRUE; // I belive that a window should always be able to present to a surface in metal
}
