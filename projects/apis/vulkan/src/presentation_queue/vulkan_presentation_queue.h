#pragma once
#include "presentation_queue/gryphn_presentation_queue.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformPresentationQueue_t {
    VkSwapchainKHR swapChain;

    VkImage* swapChainImages;
    VkImageView* swapChainImageViews;
} gnPlatformPresentationQueue;

gnReturnCode createPresentationQueue(gnPresentationQueueHandle presentationQueue, const gnDevice device, gnPresentationQueueInfo presentationInfo);
gnReturnCode getVulkanPresentQueueImage(gnPresentationQueueHandle presentationQueue, uint32_t* imageIndex);
gnReturnCode getPresentQueueImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphore semaphore, uint32_t* imageIndex);
void destroyPresentationQueue(gnPresentationQueueHandle queue);
