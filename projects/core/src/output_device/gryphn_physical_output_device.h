#pragma once
#include "stdint.h"
#include "utils/gryphn_string.h"
#include "gryphn_handles.h"

typedef enum gnDeviceType {
    GN_DEDICATED_DEVICE, GN_INTEGRATED_DEVICE, GN_EXTERNAL_DEVICE
} gnDeviceType;

typedef enum gnMultisampleCountFlags {
    GN_SAMPLE_BIT_1  = 1 << 0, // 0x01
    GN_SAMPLE_BIT_2  = 1 << 1, // 0x02
    GN_SAMPLE_BIT_4  = 1 << 2, // 0x04
    GN_SAMPLE_BIT_8  = 1 << 3, // 0x08
    GN_SAMPLE_BIT_16 = 1 << 4, // 0x10
    GN_SAMPLE_BIT_32 = 1 << 5, // 0x20
    GN_SAMPLE_BIT_64 = 1 << 6, // 0x40
} gnMultisampleCountFlags;

typedef struct gnPhysicalDeviceProperties {
    gnString name;
    gnDeviceType deviceType;
} gnPhysicalDeviceProperties;

typedef struct gnPhysicalDeviceFeatures {
    gnMultisampleCountFlags maxColorSamples, maxDepthSamples;
    uint32_t maxMemoryAllocations;
    uint32_t maxPushConstantSize;
} gnPhysicalDeviceFeatures;

#ifdef GN_REVEAL_IMPL
typedef struct gnPhysicalOutputDevice_t {
    struct gnPlatformPhysicalDevice_t* physicalDevice;
    gnPhysicalDeviceProperties properties;
    gnPhysicalDeviceFeatures features;

    gnInstanceHandle instance;
} gnPhysicalOutputDevice_t;
#endif

gnPhysicalOutputDeviceHandle* gnGetPhyscialDevices(gnInstanceHandle instance, uint32_t* count);
gnBool gnPhysicalDeviceCanPresentToSurface(gnPhysicalOutputDeviceHandle device, gnWindowSurfaceHandle windowSurface);

gnPhysicalDeviceProperties gnGetPhysicalDeviceProperties(gnPhysicalOutputDeviceHandle device);
gnPhysicalDeviceFeatures gnGetPhysicalDeviceFeatures(gnPhysicalOutputDeviceHandle device);
