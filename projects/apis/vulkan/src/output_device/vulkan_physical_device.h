#pragma once
#include <vulkan/vulkan.h>
#include <output_device/gryphn_physical_output_device.h>

typedef struct vulkanNeededQueue {
    VkQueueFlags createFlags;
    gnBool usedForPresent;
    uint32_t queueIndex;
} vulkanNeededQueue;

typedef struct gnPlatformPhysicalDevice_t {
    VkPhysicalDevice device;
    uint32_t neededQueueCount;
    vulkanNeededQueue* neededQueues;

} gnPlatformPhysicalDevice;

gnPhysicalDevice* getPhysicalDevices(gnInstanceHandle instance, uint32_t* deviceCount);
gnBool deviceCanPresentToSurface(gnPhysicalDevice device, gnWindowSurface surface);


gnMultisampleCountFlags vkSampleCountToGryphn(VkSampleCountFlags counts);
VkSampleCountFlags gnSampleCountToVulkan(gnMultisampleCountFlags counts);
