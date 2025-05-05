#include "core/presentation_queue/gryphn_presentation_queue.h"
#include "vulkan_queue_families.h"
#include "vulkan_swapchain_support.h"
#include "vulkan_presentation_queue.h"
#include "../sync_objects/vulkan_sync_semaphore.h"
#include "../textures/vulkan_texture.h"
#include "../instance/vulkan_instance.h"

GN_EXPORT gnImageFormat gnPresentationQueueGetImageFormatFn(gnPresentationQueue& presentationQueue) {
    return (gnImageFormat)presentationQueue.presentationQueue->swapchainDetails.surfaceFormat.format;
}

GN_EXPORT gnReturnCode gnCreatePresentationQueueFn(gnPresentationQueue* presentationQueue, const gnOutputDevice& device, gnPresentationDetails& details) {
    presentationQueue->presentationQueue = new gnPlatformPresentationQueue();
    presentationQueue->presentationQueue->outputDevice = const_cast<gnOutputDevice*>(&device);

    vulkanSwapchainDetails swapchain_details = vulkanGetSwapchainDetails(
            device.physicalOutputDevice->physicalOutputDevice->instance->instance->window,
            device.physicalOutputDevice->physicalOutputDevice->instance->instance->window_surface,
            device.physicalOutputDevice->physicalOutputDevice->device
    );
    presentationQueue->presentationQueue->swapchainDetails = swapchain_details;

    //std::cout << "Swapchain Image Format: " << presentationQueue->presentation_queue->swapchainDetails.surfaceFormat << "\n";

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = device.physicalOutputDevice->physicalOutputDevice->instance->instance->window_surface;

    createInfo.minImageCount = details.ImageCount;
    createInfo.imageFormat = swapchain_details.surfaceFormat.format;
    createInfo.imageColorSpace = swapchain_details.surfaceFormat.colorSpace;
    createInfo.imageExtent = swapchain_details.extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    details.ImageSize = { swapchain_details.extent.width, swapchain_details.extent.height };

    QueueFamilyIndices indices = findQueueFamilies(device.physicalOutputDevice->physicalOutputDevice->instance->instance->window_surface, device.physicalOutputDevice->physicalOutputDevice->device);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    createInfo.preTransform = swapchain_details.swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = swapchain_details.presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(device.outputDevice->device, &createInfo, nullptr, &presentationQueue->presentationQueue->swapChain) != VK_SUCCESS) {
        GN_RETURN_ERROR("failed to create swap chain!");
    }

    std::vector<VkImage> swapChainImages;
    vkGetSwapchainImagesKHR(device.outputDevice->device, presentationQueue->presentationQueue->swapChain, &details.ImageCount, nullptr);
    swapChainImages.resize(details.ImageCount);
    vkGetSwapchainImagesKHR(device.outputDevice->device, presentationQueue->presentationQueue->swapChain, &details.ImageCount, swapChainImages.data());

    presentationQueue->valid = true;
    presentationQueue->presentationQueue->device = &device.outputDevice->device;

    if (gnListLength(presentationQueue->images) < swapChainImages.size()) {
        for (size_t i = gnListLength(presentationQueue->images); i < swapChainImages.size(); i++) {
            gnTexture newImage = gnTexture();
            newImage.texture = new gnPlatformTexture();
            gnListAdd(presentationQueue->images, newImage);
        }
    }

    for (size_t i = 0; i < swapChainImages.size(); i++) {
        VkImageView imageView;
        gnReturnCode code = createImageView(device, swapChainImages[i], swapchain_details.surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT, &imageView);
        presentationQueue->images[i].texture->textureImageView = imageView;
        presentationQueue->images[i].texture->textureImage = swapChainImages[i];
        presentationQueue->images[i].texture->outputDevice = const_cast<gnOutputDevice*>(&device);
        presentationQueue->images[i].texture->swapchainImage = true;
        if (code != GN_SUCCESS) return code;
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyPresentationQueueFn(gnPresentationQueue& queue) {
    for (size_t i = 0; i < gnListLength(queue.images); i++)
        vkDestroyImageView(*queue.presentationQueue->device, queue.images[i].texture->textureImageView, nullptr);
    vkDestroySwapchainKHR(*queue.presentationQueue->device, queue.presentationQueue->swapChain, nullptr);
}

GN_EXPORT gnReturnCode gnPresentationQueueGetNextImageAsyncFn(gnPresentationQueue& presentationQueue, const gnSyncSemaphore& semaphore, gnUInt* imageIndex) {
    gnUInt nextImageIndex = 0;
    presentationQueue.presentationQueue->result =
        vkAcquireNextImageKHR(*presentationQueue.presentationQueue->device, presentationQueue.presentationQueue->swapChain, UINT64_MAX, semaphore.semaphore->semaphore, VK_NULL_HANDLE, &nextImageIndex);
    *imageIndex = nextImageIndex;

    if (presentationQueue.presentationQueue->result != VK_SUCCESS) {
        return GN_FAILED;
    }

    return GN_SUCCESS;
}

GN_EXPORT gnPresentationQueueState gnPresentationQueueGetStateFn(gnPresentationQueue& presentationQueue) {
    if (presentationQueue.presentationQueue->result == VK_ERROR_OUT_OF_DATE_KHR) {
        return GN_OUT_OF_DATE;
    } else if (presentationQueue.presentationQueue->result == VK_SUBOPTIMAL_KHR) {
        return GN_SUBOPTIMAL;
    }
    else if (presentationQueue.presentationQueue->result == VK_SUCCESS) {
        return GN_VALID;
    }
    return GN_VALID;
}
