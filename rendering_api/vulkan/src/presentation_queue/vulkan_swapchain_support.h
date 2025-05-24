#pragma once
#include <vulkan/vulkan.h>
#include <output_device/vulkan_output_devices.h>

typedef struct vkSwapchainSupportDetails_t {
    VkSurfaceCapabilitiesKHR capabilities;
    uint32_t formatCount;
    VkSurfaceFormatKHR* formats;

    uint32_t presentModeCount;
    VkPresentModeKHR* presentModes;
} vkSwapchainSupportDetails;

typedef struct vkSwapchainDetails_t {
    VkSurfaceFormatKHR surfaceFormat;
} vkSwapchainDetails;

struct vkSwapchainSupportDetails_t vkGetSwapchainSupport(
    const VkPhysicalDevice device,
    const VkSurfaceKHR surface
);

struct vkSwapchainDetails_t vkGetSwapchainDetails(
    const struct vkSwapchainSupportDetails_t supportDetails
);
