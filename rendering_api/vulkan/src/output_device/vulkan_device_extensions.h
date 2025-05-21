#pragma once
#include <vulkan/vulkan.h>
#include "vector"

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    "VK_KHR_portability_subset"
};
