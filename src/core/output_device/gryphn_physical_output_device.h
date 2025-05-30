#pragma once
#include "core/instance/gryphn_instance.h"

struct gnPlatformPhysicalDevice_t;
struct gnWindowSurface_t;

typedef enum gnDeviceType_e {
    GN_DEDICATED_DEVICE, GN_INTEGRATED_DEVICE, GN_EXTERNAL_DEVICE
} gnDeviceType;

typedef struct gnPhysicalDeviceProperties_t {
    gnString name;
    gnDeviceType deviceType;
} gnPhysicalDeviceProperties;

typedef struct gnPhysicalDeviceFeatures_t {
    gnBool supportsGeometryShader;
} gnPhysicalDeviceFeatures;

typedef enum gnQueueTypeFlags_e {
    GN_QUEUE_GRAPHICS = 0x00000001,
    GN_QUEUE_COMPUTE = 0x00000002,
    GN_QUEUE_TRANSFER = 0x00000004,
    GN_QUEUE_SPARSE_BINDING = 0x00000008
} gnQueueTypeFlags;

typedef struct gnQueueProperties_t {
    uint32_t queueCount;
    enum gnQueueTypeFlags_e queueType;
} gnQueueProperties;

typedef struct gnPhysicalDeviceQueueProperties_t {
    uint32_t queueCount;
    struct gnQueueProperties_t* queueProperties;
} gnPhysicalDeviceQueueProperties;

typedef struct gnPhysicalDevice_t {
    struct gnPlatformPhysicalDevice_t* physicalDevice;
    struct gnPhysicalDeviceProperties_t properties;
    struct gnPhysicalDeviceFeatures_t features;
    struct gnPhysicalDeviceQueueProperties_t queueProperties;

    gnInstance* instance;
} gnPhysicalDevice;

gnPhysicalDevice* gnGetPhyscialDevices(gnInstance* instance, uint32_t* count);
gnBool gnQueueCanPresentToSurface(const struct gnPhysicalDevice_t device, uint32_t queueIndex, const struct gnWindowSurface_t windowSurface);

gnBool gnHasGraphicsQueue(const struct gnPhysicalDevice_t device);
gnBool gnHasPresentQueue(const struct gnPhysicalDevice_t device, struct gnWindowSurface_t windowSurface);

int gnGetGraphicsQueueIndex(const struct gnPhysicalDevice_t device);
int gnGetPresentQueueIndex(const struct gnPhysicalDevice_t device, struct gnWindowSurface_t windowSurface);
