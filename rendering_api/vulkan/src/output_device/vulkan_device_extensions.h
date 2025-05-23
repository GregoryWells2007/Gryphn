#pragma once
#include <vulkan/vulkan.h>

const uint32_t deviceExtensionCount = 2;
static const char* deviceExtensions[2] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    "VK_KHR_portability_subset"
};
