#pragma once
#include <vulkan/vulkan.h>
#include "utils/gryphn_bool.h"

struct gnPlatformBuffer_t {
    VkBuffer buffer;
    VkDeviceMemory bufferMemory;

    // for if static draw
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    gnBool useStagingBuffer;
};
