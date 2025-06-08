#pragma once
#include <vulkan/vulkan.h>
#include "utils/gryphn_bool.h"
#include <core/buffers/gryphn_buffer.h>

typedef struct VkGryphnBuffer {
    VkBuffer buffer;
    VkDeviceMemory memory;
} VkGryphnBuffer;

struct gnPlatformBuffer_t {
    VkGryphnBuffer buffer;

    // for if static draw
    VkGryphnBuffer stagingBuffer;
    gnBool useStagingBuffer;
};

gnReturnCode VkCreateBuffer(
    VkGryphnBuffer*, gnBufferInfo info,
    VkDevice device, VkPhysicalDevice physcialDevice,
    VkMemoryPropertyFlags flags, VkBufferUsageFlags usage
);
