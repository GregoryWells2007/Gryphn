#include <presentation_queue/vulkan_presentation_queue.h>
#include "vulkan_swapchain_support.h"
#include <output_device/vulkan_physical_device.h>
#include "vulkan_surface/vulkan_surface.h"
#include "core/debugger/gryphn_debugger.h"
#include "textures/vulkan_texture.h"
#include "sync/semaphore/vulkan_semaphore.h"
#include "stdio.h"

gnReturnCode gnCreatePresentationQueueFn(gnPresentationQueueHandle presentationQueue, const gnOutputDeviceHandle device, struct gnPresentationQueueInfo_t presentationInfo) {
    presentationQueue->presentationQueue = malloc(sizeof(struct gnPlatformPresentationQueue_t));

    vkSwapchainSupportDetails details = vkGetSwapchainSupport(device->physicalDevice.physicalDevice->device, presentationInfo.surface->windowSurface->surface);

    if (details.capabilities.currentExtent.width != presentationInfo.imageSize.x || details.capabilities.currentExtent.height != presentationInfo.imageSize.y) {
        gnDebuggerSetErrorMessage(device->instance->debugger,
          (gnMessageData){
              .message = gnCreateString("Image size is unsupposed for presentation queue")
          }
        );

        presentationInfo.imageSize = (gnUInt2){ details.capabilities.currentExtent.width, details.capabilities.currentExtent.height };
    }

    if (details.formatCount == 0) {
        gnDebuggerSetErrorMessage(device->instance->debugger,
          (gnMessageData){
              .message = gnCreateString("Format count for presentation queue is zero")
          }
        );
        return GN_NO_SUPPORTED_FORMATS;
    }
    if (details.presentModeCount == 0) {
        gnDebuggerSetErrorMessage(device->instance->debugger,
          (gnMessageData){
              .message = gnCreateString("Present mode count for presentation queue is zero")
          }
        );
        return GN_NO_SUPPORTED_PRESENT_MODES;
    }

    int index = -1;
    VkFormat convertedFormat = vkGryphnFormatToVulkanFormat(presentationInfo.format.format);
    VkColorSpaceKHR convertedColorSpace = vkGryphnColorSpaceToVulkanColorSpace(presentationInfo.format.colorSpace);
    for (int i = 0; i < details.formatCount; i++) {
        if (details.formats[i].format == convertedFormat && details.formats[i].colorSpace == convertedColorSpace) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Unsupported color format passed to Gryphn")
        });
        return GN_UNKNOWN_IMAGE_FORMAT;
    }
    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
    VkExtent2D extent = {
        .width = presentationInfo.imageSize.x,
        .height = presentationInfo.imageSize.y
    };

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = presentationInfo.surface->windowSurface->surface;

    createInfo.minImageCount = presentationInfo.minImageCount;
    createInfo.imageFormat = details.formats[index].format;
    createInfo.imageColorSpace = details.formats[index].colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    if (presentationInfo.imageSharingMode == GN_SHARING_MODE_EXCLUSIVE)
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    else
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = presentationInfo.queueFamilyCount;
    createInfo.pQueueFamilyIndices = presentationInfo.queueFamilies;
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

gnReturnCode gnPresentationQueueGetImageFn(gnPresentationQueueHandle presentationQueue, uint64_t timeout, struct gnSemaphore_t* semaphore, uint32_t* imageIndex) {
    VkResult result = vkAcquireNextImageKHR(
        presentationQueue->outputDevice->outputDevice->device,
        presentationQueue->presentationQueue->swapChain,
        timeout, semaphore->semaphore->semaphore, VK_NULL_HANDLE, imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) return GN_OUT_OF_DATE_PRESENTATION_QUEUE;
    if (result == VK_SUBOPTIMAL_KHR) return GN_SUBOPTIMAL_PRESENTATION_QUEUE;

    return GN_SUCCESS;
}

void gnDestroyPresentationQueueFn(gnPresentationQueueHandle queue) {
    for (int i = 0; i < queue->imageCount; i++)
        vkDestroyImageView(queue->outputDevice->outputDevice->device, queue->presentationQueue->swapChainImageViews[i], NULL);
    vkDestroySwapchainKHR(queue->outputDevice->outputDevice->device, queue->presentationQueue->swapChain, NULL);
    free(queue->presentationQueue->swapChainImageViews);
    free(queue->presentationQueue->swapChainImages);
    free(queue->presentationQueue);
}
