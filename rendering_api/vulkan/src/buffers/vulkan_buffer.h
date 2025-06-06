#pragma once
#include <vulkan/vulkan.h>

struct gnPlatformBuffer_t {
    VkBuffer buffer;
    VkDeviceMemory bufferMemory;
};
