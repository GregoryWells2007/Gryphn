#include <presentation_queue/vulkan_presentation_queue.h>
#include "vulkan_swapchain_support.h"
#include <output_device/vulkan_physical_device.h>
#include "vulkan_surface/vulkan_surface.h"
#include "textures/vulkan_texture.h"
#include "sync/semaphore/vulkan_semaphore.h"
#include "stdio.h"

gnReturnCode createPresentationQueue(gnPresentationQueueHandle presentationQueue, const gnDevice device, gnPresentationQueueInfo presentationInfo) {
    presentationQueue->presentationQueue = malloc(sizeof(struct gnPlatformPresentationQueue_t));

    vkSwapchainSupportDetails details = vkGetSwapchainSupport(device->physicalDevice->physicalDevice->device, presentationInfo.surface->windowSurface->surface);
    VkFormat convertedFormat = vkGryphnFormatToVulkanFormat(presentationInfo.format.format);
    VkColorSpaceKHR convertedColorSpace = vkGryphnColorSpaceToVulkanColorSpace(presentationInfo.format.colorSpace);

    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
    VkExtent2D extent = {
        .width = presentationInfo.imageSize.x,
        .height = presentationInfo.imageSize.y
    };

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = presentationInfo.surface->windowSurface->surface;

    createInfo.minImageCount = presentationInfo.minImageCount;
    createInfo.imageFormat = convertedFormat;
    createInfo.imageColorSpace = convertedColorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    if (device->instance->enabledExtensions[GN_EXT_QUEUES]) {
        createInfo.imageSharingMode = (presentationInfo.imageSharingMode == GN_SHARING_MODE_CONCURRENT) ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = presentationInfo.queueFamilyCount;
        createInfo.pQueueFamilyIndices = presentationInfo.queueFamilies;
    } else {
        if (presentationInfo.surface->windowSurface->presentQueueIndex != device->outputDevice->graphicsQueueIndex) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = (uint32_t[]){
                device->outputDevice->queues[presentationInfo.surface->windowSurface->presentQueueIndex].queueInfo.queueIndex,
                device->outputDevice->queues[device->outputDevice->graphicsQueueIndex].queueInfo.queueIndex
            };
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 1;
            createInfo.pQueueFamilyIndices = &device->outputDevice->queues[presentationInfo.surface->windowSurface->presentQueueIndex].queueInfo.queueIndex;
        }
    }
    createInfo.preTransform = details.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkResult result = vkCreateSwapchainKHR(device->outputDevice->device, &createInfo, NULL, &presentationQueue->presentationQueue->swapChain);
    if (result == VK_ERROR_NATIVE_WINDOW_IN_USE_KHR) return GN_WINDOW_IN_USE;
    if (result != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_PRESENTATION_QUEUE;

    vkGetSwapchainImagesKHR(device->outputDevice->device, presentationQueue->presentationQueue->swapChain, &presentationQueue->imageCount, NULL);
    presentationQueue->presentationQueue->swapChainImages = malloc(sizeof(VkImage) * presentationQueue->imageCount);
    presentationQueue->presentationQueue->swapChainImageViews = malloc(sizeof(VkImageView) * presentationQueue->imageCount);
    vkGetSwapchainImagesKHR(device->outputDevice->device, presentationQueue->presentationQueue->swapChain, &presentationQueue->imageCount, presentationQueue->presentationQueue->swapChainImages);

    VkImageViewCreateInfo imageViewCreateInfo = {};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.format = convertedFormat;
    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount = 1;

    presentationQueue->images = malloc(sizeof(gnTextureHandle) * presentationQueue->imageCount);
    for (int i = 0; i < presentationQueue->imageCount; i++) {
        presentationQueue->images[i] = malloc(sizeof(struct gnTexture_t));
        presentationQueue->images[i]->texture = malloc(sizeof(gnPlatformTexture));
        imageViewCreateInfo.image = presentationQueue->presentationQueue->swapChainImages[i];
        if (vkCreateImageView(device->outputDevice->device, &imageViewCreateInfo, NULL, &presentationQueue->presentationQueue->swapChainImageViews[i]) != VK_SUCCESS)
            return GN_FAILED_TO_CREATE_IMAGE_VIEW;

        presentationQueue->images[i]->texture->image.image = presentationQueue->presentationQueue->swapChainImages[i];
        presentationQueue->images[i]->texture->image.imageView = presentationQueue->presentationQueue->swapChainImageViews[i];
    }

    return GN_SUCCESS;
}

gnReturnCode getVulkanPresentQueueImage(gnPresentationQueueHandle presentationQueue, uint32_t* imageIndex) {
    vkResetFences(presentationQueue->outputDevice->outputDevice->device, 1, &presentationQueue->outputDevice->outputDevice->barrierFence);
    VkResult result = vkAcquireNextImageKHR(
        presentationQueue->outputDevice->outputDevice->device,
        presentationQueue->presentationQueue->swapChain,
        UINT64_MAX, VK_NULL_HANDLE, presentationQueue->outputDevice->outputDevice->barrierFence, imageIndex);
    vkWaitForFences(presentationQueue->outputDevice->outputDevice->device, 1, &presentationQueue->outputDevice->outputDevice->barrierFence, VK_TRUE, UINT64_MAX);
    if (result == VK_ERROR_OUT_OF_DATE_KHR) return GN_OUT_OF_DATE_PRESENTATION_QUEUE;
    if (result == VK_SUBOPTIMAL_KHR) return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
    return GN_SUCCESS;
}

gnReturnCode getPresentQueueImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphore semaphore, uint32_t* imageIndex) {
    VkResult result = vkAcquireNextImageKHR(
        presentationQueue->outputDevice->outputDevice->device,
        presentationQueue->presentationQueue->swapChain,
        timeout, semaphore->semaphore->semaphore, VK_NULL_HANDLE, imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR) return GN_OUT_OF_DATE_PRESENTATION_QUEUE;
    if (result == VK_SUBOPTIMAL_KHR) return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
    return GN_SUCCESS;
}

void destroyPresentationQueue(gnPresentationQueueHandle queue) {
    for (int i = 0; i < queue->imageCount; i++)
        vkDestroyImageView(queue->outputDevice->outputDevice->device, queue->presentationQueue->swapChainImageViews[i], NULL);
    vkDestroySwapchainKHR(queue->outputDevice->outputDevice->device, queue->presentationQueue->swapChain, NULL);
    free(queue->presentationQueue->swapChainImageViews);
    free(queue->presentationQueue->swapChainImages);
    free(queue->presentationQueue);
}
