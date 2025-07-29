#pragma once
#include <output_device/gryphn_physical_output_device.h>
#include <core/gryphn_return_code.h>

typedef struct gnOutputDeviceEnabledFeatures {

} gnOutputDeviceEnabledFeatures;

typedef struct gnDeviceQueueInfo {
    int queueFamilyIndex;
    int queueCount;
    float* queuePrioritys;
} gnDeviceQueueInfo;

typedef struct gnOutputDeviceInfo {
    uint32_t queueInfoCount;
    gnDeviceQueueInfo* queueInfos; // only used if GN_EXT_QUEUES is enabled

    gnOutputDeviceEnabledFeatures enabledFeatures;
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
