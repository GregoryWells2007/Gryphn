#include <presentation_queue/vulkan_presentation_queue.h>
#include "vulkan_swapchain_support.h"
#include <output_device/vulkan_physical_device.h>
#include "vulkan_surface/vulkan_surface.h"
#include "textures/vulkan_texture.h"
#include "sync/semaphore/vulkan_semaphore.h"
#include <vulkan_result_converter.h>

#include "stdio.h"

gnReturnCode createPresentationQueue(gnPresentationQueueHandle presentationQueue, const gnDevice device, gnPresentationQueueInfo presentationInfo) {
    presentationQueue->presentationQueue = malloc(sizeof(struct gnPlatformPresentationQueue_t));

    vkSwapchainSupportDetails details = vkGetSwapchainSupport(device->outputDevice->physicalDevice, presentationInfo.surface->windowSurface->surface);
    VkFormat convertedFormat = vkGryphnFormatToVulkanFormat(presentationInfo.format.format);
    VkColorSpaceKHR convertedColorSpace = vkGryphnColorSpaceToVulkanColorSpace(presentationInfo.format.colorSpace);

    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
    VkExtent2D extent = {
        .width = presentationInfo.imageSize.x,
        .height = presentationInfo.imageSize.y
    };

    VkSwapchainCreateInfoKHR presentQueueCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = presentationInfo.surface->windowSurface->surface,
        .minImageCount = presentationInfo.minImageCount,
        .imageFormat = convertedFormat,
        .imageColorSpace = convertedColorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .preTransform = details.capabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE
    };

    if (device->instance->enabledExtensions[GN_EXT_QUEUES]) {
        presentQueueCreateInfo.imageSharingMode = (presentationInfo.imageSharingMode == GN_SHARING_MODE_CONCURRENT) ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
        presentQueueCreateInfo.queueFamilyIndexCount = presentationInfo.queueFamilyCount;
        presentQueueCreateInfo.pQueueFamilyIndices = presentationInfo.queueFamilies;
    } else {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device->outputDevice->physicalDevice, &queueFamilyCount, NULL);
        for (uint32_t i = 0; i < queueFamilyCount; i++) {
            VkBool32 supportsPresent;
            vkGetPhysicalDeviceSurfaceSupportKHR(device->outputDevice->physicalDevice, i, presentationInfo.surface->windowSurface->surface, &supportsPresent);
            if (supportsPresent) { presentationQueue->presentationQueue->presentQueueIndex = i; break; };
        }

        if (presentationQueue->presentationQueue->presentQueueIndex != device->outputDevice->graphicsQueueIndex) {
            presentQueueCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            presentQueueCreateInfo.queueFamilyIndexCount = 2;
            presentQueueCreateInfo.pQueueFamilyIndices = (uint32_t[]){
                presentationQueue->presentationQueue->presentQueueIndex,
                device->outputDevice->queues[device->outputDevice->graphicsQueueIndex].queueInfo.queueIndex
            };
        } else {
            presentQueueCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            presentQueueCreateInfo.queueFamilyIndexCount = 1;
            presentQueueCreateInfo.pQueueFamilyIndices = &presentationQueue->presentationQueue->presentQueueIndex;
        }
    }

    VkResult result = vkCreateSwapchainKHR(device->outputDevice->device, &presentQueueCreateInfo, NULL, &presentationQueue->presentationQueue->swapChain);
    if (result != VK_SUCCESS) return VkResultToGnReturnCode(result);

    vkGetSwapchainImagesKHR(device->outputDevice->device, presentationQueue->presentationQueue->swapChain, &presentationQueue->imageCount, NULL);
    presentationQueue->presentationQueue->swapChainImages = malloc(sizeof(VkImage) * presentationQueue->imageCount);
    presentationQueue->presentationQueue->swapChainImageViews = malloc(sizeof(VkImageView) * presentationQueue->imageCount);
    vkGetSwapchainImagesKHR(device->outputDevice->device, presentationQueue->presentationQueue->swapChain, &presentationQueue->imageCount, presentationQueue->presentationQueue->swapChainImages);

    VkImageViewCreateInfo imageViewCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = convertedFormat,
        .components.r = VK_COMPONENT_SWIZZLE_IDENTITY,
        .components.g = VK_COMPONENT_SWIZZLE_IDENTITY,
        .components.b = VK_COMPONENT_SWIZZLE_IDENTITY,
        .components.a = VK_COMPONENT_SWIZZLE_IDENTITY,
        .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .subresourceRange.baseMipLevel = 0,
        .subresourceRange.levelCount = 1,
        .subresourceRange.baseArrayLayer = 0,
        .subresourceRange.layerCount = 1
    };

    presentationQueue->images = malloc(sizeof(gnTextureHandle) * presentationQueue->imageCount);
    for (uint32_t i = 0; i < presentationQueue->imageCount; i++) {
        presentationQueue->images[i] = malloc(sizeof(struct gnTexture_t));
        presentationQueue->images[i]->texture = malloc(sizeof(gnPlatformTexture));
        imageViewCreateInfo.image = presentationQueue->presentationQueue->swapChainImages[i];
        VkResult creatingImageViewResult = vkCreateImageView(device->outputDevice->device, &imageViewCreateInfo, NULL, &presentationQueue->presentationQueue->swapChainImageViews[i]);
        if (creatingImageViewResult != VK_SUCCESS)
            return VkResultToGnReturnCode(creatingImageViewResult);

        presentationQueue->images[i]->texture->image.image = presentationQueue->presentationQueue->swapChainImages[i];
        presentationQueue->images[i]->texture->image.imageView = presentationQueue->presentationQueue->swapChainImageViews[i];
    }

    return VkResultToGnReturnCode(result);
}

gnReturnCode getVulkanPresentQueueImage(gnPresentationQueueHandle presentationQueue, uint32_t* imageIndex) {
    vkResetFences(presentationQueue->outputDevice->outputDevice->device, 1, &presentationQueue->outputDevice->outputDevice->barrierFence);
    VkResult result = vkAcquireNextImageKHR(
        presentationQueue->outputDevice->outputDevice->device,
        presentationQueue->presentationQueue->swapChain,
        UINT64_MAX, VK_NULL_HANDLE, presentationQueue->outputDevice->outputDevice->barrierFence, imageIndex);
    vkWaitForFences(presentationQueue->outputDevice->outputDevice->device, 1, &presentationQueue->outputDevice->outputDevice->barrierFence, VK_TRUE, UINT64_MAX);
    return VkResultToGnReturnCode(result);
}

gnReturnCode getPresentQueueImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphore semaphore, uint32_t* imageIndex) {
    return VkResultToGnReturnCode(vkAcquireNextImageKHR(
        presentationQueue->outputDevice->outputDevice->device,
        presentationQueue->presentationQueue->swapChain,
        timeout, semaphore->semaphore->semaphore, VK_NULL_HANDLE, imageIndex));
}

void destroyPresentationQueue(gnPresentationQueueHandle queue) {
    for (uint32_t i = 0; i < queue->imageCount; i++)
        vkDestroyImageView(queue->outputDevice->outputDevice->device, queue->presentationQueue->swapChainImageViews[i], NULL);
    vkDestroySwapchainKHR(queue->outputDevice->outputDevice->device, queue->presentationQueue->swapChain, NULL);
    free(queue->presentationQueue->swapChainImageViews);
    free(queue->presentationQueue->swapChainImages);
    free(queue->presentationQueue);
}
