#pragma once
#include <vulkan/vulkan.h>
#include <output_device/gryphn_physical_output_device.h>

typedef struct gnPlatformPhysicalDevice_t {
    VkPhysicalDevice device;
} gnPlatformPhysicalDevice;

gnPhysicalDevice* getPhysicalDevices(gnInstanceHandle instance, uint32_t* deviceCount);
gnBool queueCanPresentToSurface(const gnPhysicalDevice device, uint32_t queueIndex, gnWindowSurfaceHandle windowSurface);


gnMultisampleCountFlags vkSampleCountToGryphn(VkSampleCountFlags counts);
VkSampleCountFlags gnSampleCountToVulkan(gnMultisampleCountFlags counts);
