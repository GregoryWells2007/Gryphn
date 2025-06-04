#pragma once
#include <core/output_device/gryphn_physical_output_device.h>
#include <utils/gryphn_error_code.h>

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

#ifdef GN_REVEAL_IMPL
struct gnOutputDevice_t {
    struct gnPlatformOutputDevice_t* outputDevice;
    struct gnDeviceFunctions_t* deviceFunctions;
    struct gnOutputDeviceInfo_t deviceInfo;
    gnInstanceHandle instance;
    gnPhysicalDevice physicalDevice;
};
#endif

gnReturnCode gnCreateOutputDevice(gnOutputDeviceHandle* outputDevice, gnInstanceHandle instance, struct gnOutputDeviceInfo_t deviceInfo);
void gnWaitForDevice(gnOutputDeviceHandle device);
void gnDestroyOutputDevice(gnOutputDeviceHandle device);
