#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/instance/gryphn_instance.h"

struct gnPlatformPhysicalOutputDevice;
struct gnInstance;

struct gnPhysicalOutputDevice {
ACCESS_LEVEL:
    bool valid = false;
    gnPlatformPhysicalOutputDevice* physicalOutputDevice = nullptr;
    gnString outputDeviceName;
public:
    gnPhysicalOutputDevice() {}
};

gnString gnGetPhysicalOutputDeviceName(const gnPhysicalOutputDevice& device);
inline bool (*gnDeviceSupportsAPI)(const gnPhysicalOutputDevice& device);
inline gnList<gnPhysicalOutputDevice> (*gnGetPhysicalOutputDevices)(const gnInstance& instance);
