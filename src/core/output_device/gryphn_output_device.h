#pragma once
#include <core/output_device/gryphn_physical_output_device.h>

struct gnPlatformOutputDevice;
struct gnDeviceFunctions_t;

typedef struct gnOutputDevice_t {
    struct gnPlatformOutputDevice* outputDevice;
    struct gnDeviceFunctions_t* deviceFunctions;
    gnPhysicalDevice* physicalDevice;
} gnOutputDevice;

gnReturnCode gnRegisterOutputDevice(gnOutputDevice* outputDevice, gnInstance* instance, const gnPhysicalDevice physicalDevice);
void gnDestroyOutputDevice(gnOutputDevice* device);

// inline void (*gnWaitForDevice)(const gnOutputDevice& device);
