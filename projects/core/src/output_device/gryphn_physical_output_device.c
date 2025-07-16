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
