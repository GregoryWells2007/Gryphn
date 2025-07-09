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
    gnBool useStagingBuffer;
};

gnReturnCode VkCreateBuffer(
    VkGryphnBuffer* buffer, size_t size, gnDevice device,
    VkMemoryPropertyFlags flags, VkBufferUsageFlags usage
);
void gnDestroyVulkanBuffer(VkGryphnBuffer* buffer, VkDevice device);
uint32_t VkMemoryIndex(VkPhysicalDevice device, uint32_t memoryType, VkMemoryPropertyFlags flags, gnBool* foundMemory);

gnReturnCode createBuffer(gnBufferHandle buffer, gnOutputDeviceHandle device, gnBufferInfo info);
void bufferData(gnBufferHandle buffer, size_t dataSize, void* data);
void vulkanBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, void* data);
void* mapBuffer(gnBufferHandle buffer);
void destroyBuffer(gnBufferHandle buffer);
