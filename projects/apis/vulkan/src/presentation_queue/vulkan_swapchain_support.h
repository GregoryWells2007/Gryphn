#pragma once
#include <vulkan/vulkan.h>
#include <output_device/vulkan_output_devices.h>

typedef struct vkSwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    uint32_t formatCount;
    VkSurfaceFormatKHR* formats;

    uint32_t presentModeCount;
    VkPresentModeKHR* presentModes;
} vkSwapchainSupportDetails;

typedef struct vkSwapchainDetails {
    VkSurfaceFormatKHR surfaceFormat;
} vkSwapchainDetails;

struct vkSwapchainSupportDetails vkGetSwapchainSupport(
    const VkPhysicalDevice device,
    const VkSurfaceKHR surface
);
