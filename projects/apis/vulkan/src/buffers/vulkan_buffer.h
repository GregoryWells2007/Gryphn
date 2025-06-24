#pragma once
#include <vulkan/vulkan.h>
#include "utils/gryphn_bool.h"
#include <buffers/gryphn_buffer.h>

typedef struct VkGryphnBuffer {
    VkBuffer buffer;
    VkDeviceMemory memory;
} VkGryphnBuffer;
void gnDestroyVulkanBuffer(VkGryphnBuffer* buffer, VkDevice device);

struct gnPlatformBuffer_t {
    VkGryphnBuffer buffer;

    // for if static draw
    VkGryphnBuffer stagingBuffer;
    gnBool useStagingBuffer;
};

gnReturnCode VkCreateBuffer(
    VkGryphnBuffer* buffer, size_t size, gnDevice device,
    VkMemoryPropertyFlags flags, VkBufferUsageFlags usage
);
uint32_t VkMemoryIndex(VkPhysicalDevice device, uint32_t memoryType, VkMemoryPropertyFlags flags, gnBool* foundMemory);
