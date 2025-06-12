#pragma once
#include <vulkan/vulkan.h>

#ifdef GN_PLATFORM_MACOS
static const uint32_t deviceExtensionCount = 2;
static const char* deviceExtensions[2] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    "VK_KHR_portability_subset"
};
#else
static const uint32_t deviceExtensionCount = 1;
static const char* deviceExtensions[1] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
#endif
