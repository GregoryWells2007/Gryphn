#include "gryphn_output_device.h"
#include "instance/gryphn_instance.h"
#include "gryphn_platform_functions.h"

gnReturnCode gnCreateOutputDevice(gnOutputDeviceHandle* outputDevice, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo) {
    *outputDevice = malloc(sizeof(struct gnOutputDevice_t));
    (*outputDevice)->deviceFunctions = instance->deviceFunctions;

    (*outputDevice)->instance = instance;
    (*outputDevice)->physicalDevice = deviceInfo.physicalDevice;
    (*outputDevice)->deviceInfo = deviceInfo;
    return instance->instanceFunctions._gnCreateOutputDevice(*outputDevice, instance, deviceInfo);
}
void gnWaitForDevice(gnOutputDeviceHandle device) {
    device->deviceFunctions->_gnWaitForDevice(device);
}
void gnDestroyOutputDevice(gnOutputDeviceHandle device) {
    device->instance->instanceFunctions._gnDestroyOutputDevice(device);
    free(device);
}
