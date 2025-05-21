#include "gryphn_output_device.h"
#include "core/instance/gryphn_instance.h"
#include "core/gryphn_platform_functions.h"
#include "core/instance/init/gryphn_init.h"

gnReturnCode gnRegisterOutputDevice(gnOutputDevice* outputDevice, gnInstance* instance, const gnPhysicalDevice physicalDevice) {
    outputDevice->deviceFunctions = malloc(sizeof(gnDeviceFunctions));
    gnLoadDeviceFunctions(instance->dynamicLib, outputDevice->deviceFunctions);
    outputDevice->physicalDevice = (gnPhysicalDevice*)(&physicalDevice);
    return instance->functions->_gnRegisterOutputDevice(outputDevice, instance, physicalDevice);
}
void gnDestroyOutputDevice(gnOutputDevice* device) {
    device->physicalDevice->instance->functions->_gnDestroyOutputDevice(device);
}
