#include "gryphn_physical_output_device.h"
#include "core/gryphn_platform_functions.h"

gnPhysicalDevice* gnGetPhyscialDevices(gnInstance* instance, uint32_t* count) {
    gnPhysicalDevice* devices = instance->functions->_gnGetPhysicalDevices(instance, count);
    for (int i = 0; i < *count; i++) {
        devices[i].instance = instance;
    }
    return devices;
}
gnBool gnDeviceSupportsAPI(const gnPhysicalDevice device) {
    return device.instance->functions->_gnDeviceSupportsAPI(device);
}
