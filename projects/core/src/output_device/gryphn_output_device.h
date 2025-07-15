#pragma once
#include <output_device/gryphn_physical_output_device.h>
#include <utils/gryphn_error_code.h>

// typedef struct gnDeviceQueueInfo {
//     int queueIndex;
//     int queueCount;
//     // float* queuePriority;
// } gnDeviceQueueInfo;

typedef struct gnOutputDeviceInfo {
    // uint32_t queueInfoCount;
    // gnDeviceQueueInfo* queueInfos;
    gnPhysicalDeviceFeatures enabledFeatures;
    gnPhysicalDevice physicalDevice;
} gnOutputDeviceInfo;

#ifdef GN_REVEAL_IMPL
struct gnOutputDevice_t {
    struct gnPlatformOutputDevice_t* outputDevice;
    gnOutputDeviceInfo deviceInfo;
    gnInstanceHandle instance;
    gnPhysicalDevice physicalDevice;
};
#endif

gnReturnCode gnCreateOutputDevice(gnOutputDeviceHandle* outputDevice, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo);
void gnWaitForDevice(gnOutputDeviceHandle device);
void gnDestroyOutputDevice(gnOutputDeviceHandle device);
