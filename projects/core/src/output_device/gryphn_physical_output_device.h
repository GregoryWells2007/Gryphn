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

typedef enum gnQueueTypeFlags {
    GN_QUEUE_GRAPHICS       = 1 << 0,
    GN_QUEUE_COMPUTE        = 1 << 1,
    GN_QUEUE_TRANSFER       = 1 << 2,
    GN_QUEUE_SPARSE_BINDING = 1 << 3
} gnQueueTypeFlags;

typedef struct gnQueueProperties {
    uint32_t queueCount;
    gnQueueTypeFlags queueType;
} gnQueueProperties;

typedef struct gnPhysicalDeviceQueueProperties {
    uint32_t queueCount;
    gnQueueProperties* queueProperties;
} gnPhysicalDeviceQueueProperties;

typedef struct gnPhysicalDevice {
    struct gnPlatformPhysicalDevice_t* physicalDevice;
    gnPhysicalDeviceProperties properties;
    gnPhysicalDeviceFeatures features;
    gnPhysicalDeviceQueueProperties queueProperties;

    gnInstanceHandle instance;
} gnPhysicalDevice;

gnPhysicalDevice* gnGetPhyscialDevices(gnInstanceHandle instance, uint32_t* count);
gnBool gnQueueCanPresentToSurface(const gnPhysicalDevice device, uint32_t queueIndex, gnWindowSurfaceHandle windowSurface);

gnBool gnHasGraphicsQueue(const gnPhysicalDevice device);
gnBool gnHasPresentQueue(const gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface);

int gnGetGraphicsQueueIndex(const gnPhysicalDevice device);
int gnGetPresentQueueIndex(const gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface);
