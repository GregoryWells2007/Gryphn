#include <presentation_queue/vulkan_presentation_queue.h>
#include "vulkan_swapchain_support.h"
#include <output_device/vulkan_physical_device.h>
#include "vulkan_surface/vulkan_surface.h"
#include "core/debugger/gryphn_debugger.h"

gnReturnCode gnCreatePresentationQueueFn(gnPresentationQueue* presentationQueue, const gnOutputDevice* device, struct gnPresentationQueueInfo_t presentationInfo) {
    presentationQueue->presentationQueue = malloc(sizeof(struct gnPlatformPresentationQueue_t));

    vkSwapchainSupportDetails details = vkGetSwapchainSupport(device->physicalDevice.physicalDevice->device, presentationInfo.surface.windowSurface->surface);
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
        .width = presentationInfo.ImageSize.x,
        .height = presentationInfo.ImageSize.y
    };

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = presentationInfo.surface.windowSurface->surface;

    createInfo.minImageCount = presentationInfo.ImageCount;
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

    if (vkCreateSwapchainKHR(device->outputDevice->device, &createInfo, NULL, &presentationQueue->presentationQueue->swapChain) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_PRESENTATION_QUEUE;
    }

    return GN_SUCCESS;
}

void gnDestroyPresentationQueueFn(gnPresentationQueue* queue) {
    vkDestroySwapchainKHR(queue->outputDevice->outputDevice->device, queue->presentationQueue->swapChain, NULL);
}
