#pragma once
#include "presentation_queue/gryphn_presentation_queue.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformPresentationQueue_t {
    VkSwapchainKHR swapChain;

    VkImage* swapChainImages;
    VkImageView* swapChainImageViews;
} gnPlatformPresentationQueue;
