#pragma once
#include "vulkan_swapchain_support.h"

struct gnPlatformPresentationQueue {
    VkSwapchainKHR swapChain;
    VkDevice* device;
    gnOutputDevice* outputDevice;

    vulkanSwapchainDetails swapchainDetails;
    VkResult result;
};
