#pragma once
#include "core/presentation_queue/gryphn_presentation_queue.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformPresentationQueue_t {
    VkSwapchainKHR swapChain;
    // VkDevice* device;
    // gnOutputDevice* outputDevice;

    // vulkanSwapchainDetails swapchainDetails;
    // VkResult result;
} gnPlatformPresentationQueue;
