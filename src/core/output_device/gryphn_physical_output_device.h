#pragma once
#include "core/instance/gryphn_instance.h"

struct gnPlatformPhysicalDevice;

typedef struct gnPhysicalDeviceProperties_t {
 // there are currently no properties
} gnPhysicalDeviceProperties;

typedef struct gnPhysicalDevice_t {
    struct gnPlatformPhysicalDevice* physicalDevice;
    gnString name;
    struct gnPhysicalDeviceProperties_t properties;

    gnInstance* instance;
} gnPhysicalDevice;

gnPhysicalDevice* gnGetPhyscialDevices(gnInstance* instance, uint32_t* count);
gnBool gnDeviceSupportsAPI(const gnPhysicalDevice device);
