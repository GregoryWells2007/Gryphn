#pragma once
#include "vulkan/vulkan.h"
#include "vulkan_swapchain.h"
#include "../output_device/vulkan_output_devices.h"

struct vulkanSwapchainDetails {
    VkSurfaceFormatKHR surfaceFormat;
    VkPresentModeKHR presentMode;
    VkExtent2D extent;

    SwapChainSupportDetails swapChainSupport;
};

static vulkanSwapchainDetails vulkanGetSwapchainDetails(GLFWwindow* window, const VkSurfaceKHR& surface, const VkPhysicalDevice& physicalDevice) {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(surface, physicalDevice);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(window, swapChainSupport.capabilities);

    return {
        surfaceFormat, presentMode, extent, swapChainSupport
    };
}
