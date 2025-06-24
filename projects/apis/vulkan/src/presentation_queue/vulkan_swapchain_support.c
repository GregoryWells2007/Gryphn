#include "vulkan_swapchain_support.h"

struct vkSwapchainSupportDetails_t vkGetSwapchainSupport(
    const VkPhysicalDevice device,
    const VkSurfaceKHR surface
) {
    struct vkSwapchainSupportDetails_t details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &details.formatCount, NULL);
    if (details.formatCount > 0) {
        details.formats = malloc(sizeof(VkSurfaceFormatKHR) * details.formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &details.formatCount, details.formats);
    }

    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &details.presentModeCount, NULL);
    if (details.presentModeCount > 0) {
        details.presentModes = malloc(sizeof(VkPresentModeKHR) * details.presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &details.presentModeCount, details.presentModes);
    }

    return details;
}

struct vkSwapchainDetails_t vkGetSwapchainDetails(
    const struct vkSwapchainSupportDetails_t supportDetails
) {
    struct vkSwapchainDetails_t details;

    for (int i = 0; i < supportDetails.formatCount; i++) {
        // if (supportDetails.)
    }

    return details;
}
