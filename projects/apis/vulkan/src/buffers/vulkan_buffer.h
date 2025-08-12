#pragma once
#include <vulkan/vulkan.h>
#include "utils/gryphn_bool.h"
#include <buffers/gryphn_buffer.h>
#include <memory_allocator/vk_mem_alloc.h>

typedef struct VkGryphnBuffer {
    VkBuffer buffer;
    VmaAllocation allocation;
} VkGryphnBuffer;

struct gnPlatformBuffer_t {
    VkGryphnBuffer buffer;
    gnBool useStagingBuffer;
};

// gnReturnCode VkCreateBuffer(
//     VkGryphnBuffer* buffer, size_t size, gnDevice device,
//     VkMemoryPropertyFlags flags, VkBufferUsageFlags usage
// );
// void gnDestroyVulkanBuffer(VkGryphnBuffer* buffer, gnDevice device);
// uint32_t VkMemoryIndex(VkPhysicalDevice device, uint32_t memoryType, VkMemoryPropertyFlags flags, gnBool* foundMemory);

gnReturnCode createBuffer(gnBufferHandle buffer, gnOutputDeviceHandle device, gnBufferInfo info);
void vulkanBufferData(gnBufferHandle buffer, size_t dataSize, void* data);
void vulkanBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, void* data);

void vulkanMapBufferInternal(gnDevice device, VkGryphnBuffer buffer, void* data);
void vulkanUnmapBufferInternal(gnDevice device, VkGryphnBuffer buffer);
void* vulkanMapBuffer(gnBufferHandle buffer);
void vulkanUnmapBuffer(gnBufferHandle buffer);

void destroyBuffer(gnBufferHandle buffer);
