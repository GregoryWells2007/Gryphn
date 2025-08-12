#include "vulkan_buffer.h"
#include "buffers/gryphn_buffer.h"
#include "output_device/gryphn_output_device.h"
#include "output_device/vulkan_output_devices.h"
#include <vulkan_result_converter.h>
#include "string.h"

VkBufferUsageFlags vkGryphnBufferType(gnBufferType type) {
    VkBufferUsageFlags usageFlags = 0;
    if ((type & GN_VERTEX_BUFFER) == GN_VERTEX_BUFFER) usageFlags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    if ((type & GN_INDEX_BUFFER) == GN_INDEX_BUFFER) usageFlags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    if ((type & GN_UNIFORM_BUFFER) == GN_UNIFORM_BUFFER) usageFlags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    if ((type & GN_STORAGE_BUFFER) == GN_STORAGE_BUFFER) usageFlags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    return usageFlags;
}

void VkCopyBuffer(gnDevice device, VkBuffer source, VkBuffer destination, VkBufferCopy copy) {
    VkCommandBuffer transferBuffer = gnBeginVulkanTransferOperation(device);
    vkCmdCopyBuffer(transferBuffer, source, destination, 1, &copy);
    gnEndVulkanTransferOperation(device, transferBuffer);
}

gnReturnCode createBuffer(gnBufferHandle buffer, gnOutputDeviceHandle device, gnBufferInfo info) {
    buffer->buffer = malloc(sizeof(struct gnPlatformBuffer_t));
    buffer->buffer->useStagingBuffer = (info.usage == GN_STATIC_DRAW);
    if (info.usage == GN_STATIC_DRAW) {
        VkBufferCreateInfo bufferCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .pNext = NULL,
            .flags = 0,
            .queueFamilyIndexCount = 0,
            .size = info.size,
            .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
            .usage = vkGryphnBufferType(info.type) | VK_BUFFER_USAGE_TRANSFER_DST_BIT
        };

        VmaAllocationCreateInfo bufferAllocationInfo = {
            .usage = VMA_MEMORY_USAGE_AUTO,
            .flags = 0,
            .requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        };

        return VkResultToGnReturnCode(vmaCreateBuffer(device->outputDevice->allocator, &bufferCreateInfo, &bufferAllocationInfo, &buffer->buffer->buffer.buffer, &buffer->buffer->buffer.allocation, NULL));
    } else {
        VkBufferCreateInfo bufferCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .pNext = NULL,
            .flags = 0,
            .queueFamilyIndexCount = 0,
            .size = info.size,
            .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
            .usage = vkGryphnBufferType(info.type)
        };

        VmaAllocationCreateInfo bufferAllocationInfo = {
            .usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE,
            .flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT,
            .requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        };

        return VkResultToGnReturnCode(vmaCreateBuffer(device->outputDevice->allocator, &bufferCreateInfo, &bufferAllocationInfo, &buffer->buffer->buffer.buffer, &buffer->buffer->buffer.allocation, NULL));
    }

    return GN_SUCCESS;
}
void vulkanBufferData(gnBufferHandle buffer, size_t dataSize, void* data) {
    vulkanBufferSubData(buffer, 0, dataSize, data);
}
void vulkanBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, void* data) {
    void* bufferData;
    if (buffer->buffer->useStagingBuffer) {
        VkGryphnBuffer* stagingBuffer = &buffer->device->outputDevice->stagingBuffer;
        VkDeviceSize sizeLeft = dataSize;
        while (sizeLeft > 0) {
            VkDeviceSize chunkSize = (buffer->device->outputDevice->stagingBufferSize < sizeLeft) ? buffer->device->outputDevice->stagingBufferSize : sizeLeft;
            vulkanMapBufferInternal(buffer->device, *stagingBuffer, &bufferData);
            memcpy(bufferData, (char*)data + (dataSize - sizeLeft), chunkSize);
            vulkanUnmapBufferInternal(buffer->device, *stagingBuffer);

            VkBufferCopy copyRegion = {
                .srcOffset = 0,
                .dstOffset = offset + (dataSize - sizeLeft),
                .size = chunkSize
            };
            VkCopyBuffer(buffer->device, stagingBuffer->buffer, buffer->buffer->buffer.buffer, copyRegion);
            sizeLeft -= chunkSize;
        }
    } else {
        bufferData = vulkanMapBuffer(buffer);
        memcpy((char*)bufferData + offset, data, dataSize);
        vulkanUnmapBuffer(buffer);
    }
}


void vulkanMapBufferInternal(gnDevice device, VkGryphnBuffer buffer, void* data) {
    vmaMapMemory(device->outputDevice->allocator, buffer.allocation, data);
}
void vulkanUnmapBufferInternal(gnDevice device, VkGryphnBuffer buffer) {
    vmaUnmapMemory(device->outputDevice->allocator, buffer.allocation);
}

void* vulkanMapBuffer(gnBufferHandle buffer) {
    void* data;
    vulkanMapBufferInternal(buffer->device, buffer->buffer->buffer, &data);
    return data;
}

void vulkanUnmapBuffer(gnBufferHandle buffer) {
    vulkanUnmapBufferInternal(buffer->device, buffer->buffer->buffer);
}

void gnDestroyVulkanBuffer(VkGryphnBuffer* buffer, gnDevice device) {
    vmaDestroyBuffer(device->outputDevice->allocator, buffer->buffer, buffer->allocation);
}

void destroyBuffer(gnBufferHandle buffer) {
    gnDestroyVulkanBuffer(&buffer->buffer->buffer, buffer->device);
    free(buffer->buffer);
}
