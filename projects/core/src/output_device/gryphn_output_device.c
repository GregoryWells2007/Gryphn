#include "gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnCreateOutputDevice(gnOutputDeviceHandle* outputDevice, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo) {
    *outputDevice = malloc(sizeof(struct gnOutputDevice_t));

    (*outputDevice)->instance = instance;
    (*outputDevice)->physicalDevice = deviceInfo.physicalDevice;
    (*outputDevice)->deviceInfo = deviceInfo;
    return instance->callingLayer->instanceFunctions._gnCreateOutputDevice(*outputDevice, instance, deviceInfo);
}
void gnWaitForDevice(gnOutputDeviceHandle device) {
    device->instance->callingLayer->deviceFunctions._gnWaitForDevice(device);
}
void gnDestroyOutputDevice(gnOutputDeviceHandle device) {
    device->instance->callingLayer->instanceFunctions._gnDestroyOutputDevice(device);
    free(device);
}
