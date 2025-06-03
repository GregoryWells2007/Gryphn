#include "gryphn_output_device.h"
#include "core/instance/gryphn_instance.h"
#include "core/gryphn_platform_functions.h"
#include "core/instance/init/gryphn_init.h"

gnReturnCode gnCreateOutputDevice(gnOutputDeviceHandle* outputDevice, gnInstanceHandle instance, struct gnOutputDeviceInfo_t deviceInfo) {
    *outputDevice = malloc(sizeof(struct gnOutputDevice_t));

    if (instance->loadDeviceFunctions == gnFalse) {
        instance->deviceFunctions = malloc(sizeof(struct gnDeviceFunctions_t));
        gnLoadDeviceFunctions(instance->dynamicLib, instance->deviceFunctions);
        instance->loadDeviceFunctions = gnTrue;
    }

    (*outputDevice)->deviceFunctions = instance->deviceFunctions;

    (*outputDevice)->instance = instance;
    (*outputDevice)->physicalDevice = deviceInfo.physicalDevice;
    (*outputDevice)->deviceInfo = deviceInfo;
    return instance->functions->_gnCreateOutputDevoce(*outputDevice, instance, deviceInfo);
}
void gnWaitForDevice(gnOutputDeviceHandle device) {
    device->deviceFunctions->_gnWaitForDevice(device);
}
void gnDestroyOutputDevice(gnOutputDeviceHandle device) {
    device->instance->functions->_gnDestroyOutputDevice(device);
    free(device);
}
