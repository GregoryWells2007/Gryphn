#pragma once
#include <core/output_device/gryphn_physical_output_device.h>

struct gnPlatformOutputDevice_t;
struct gnDeviceFunctions_t;

typedef struct gnDeviceQueueInfo_t {
    int queueIndex;
    int queueCount;
    // float* queuePriority;
} gnDeviceQueueInfo;

typedef struct gnOutputDeviceInfo_t {
    uint32_t queueInfoCount;
    struct gnDeviceQueueInfo_t* queueInfos;
    struct gnPhysicalDeviceFeatures_t enabledFeatures;
    struct gnPhysicalDevice_t physicalDevice;
} gnOutputDeviceInfo;

typedef struct gnOutputDevice_t {
    struct gnPlatformOutputDevice_t* outputDevice;
    struct gnDeviceFunctions_t* deviceFunctions;
    struct gnOutputDeviceInfo_t deviceInfo;
    gnInstance* instance;
    gnPhysicalDevice physicalDevice;
} gnOutputDevice;

gnReturnCode gnCreateOutputDevice(gnOutputDevice* outputDevice, gnInstance* instance, struct gnOutputDeviceInfo_t deviceInfo);
void gnDestroyOutputDevice(gnOutputDevice* device);

// inline void (*gnWaitForDevice)(const gnOutputDevice& device);
