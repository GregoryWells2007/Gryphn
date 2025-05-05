#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_physical_output_device.h"

struct gnPlatformOutputDevice;
struct gnPhysicalOutputDevice;
struct gnInstance;

struct gnOutputDevice {
ACCESS_LEVEL:
    gnPlatformOutputDevice* outputDevice = nullptr;
    gnPhysicalOutputDevice* physicalOutputDevice;
public:
    gnOutputDevice() {}
};

inline gnReturnCode (*gnRegisterOutputDevice)(gnOutputDevice* outputDevice, const gnInstance& instance, const gnPhysicalOutputDevice& physicalDevice);
inline void (*gnWaitForDevice)(const gnOutputDevice& device);
inline void (*gnDestroyOutputDevice)(gnOutputDevice& device);
