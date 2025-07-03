#pragma once
#include "stdint.h"
#include "utils/gryphn_string.h"
#include "gryphn_handles.h"

typedef enum gnDeviceType {
    GN_DEDICATED_DEVICE, GN_INTEGRATED_DEVICE, GN_EXTERNAL_DEVICE
} gnDeviceType;

typedef struct gnPhysicalDeviceProperties {
    gnString name;
    gnDeviceType deviceType;
} gnPhysicalDeviceProperties;

typedef struct gnPhysicalDeviceFeatures {
    gnBool supportsGeometryShader;
} gnPhysicalDeviceFeatures;

typedef enum gnQueueTypeFlags {
    GN_QUEUE_GRAPHICS = 1,
    GN_QUEUE_COMPUTE = 2,
    GN_QUEUE_TRANSFER = 4,
    GN_QUEUE_SPARSE_BINDING = 8
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
