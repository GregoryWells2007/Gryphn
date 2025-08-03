#include "vulkan_buffer.h"
#include "buffers/gryphn_buffer.h"
#include "output_device/gryphn_output_device.h"
#include "output_device/vulkan_output_devices.h"
#include <vulkan_result_converter.h>
#include "string.h"

VkBufferUsageFlags vkGryphnBufferType(gnBufferType type) {
    VkBufferUsageFlags usageFlags = 0;
    switch (type) {
    case GN_VERTEX_BUFFER: usageFlags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT; break;
    case GN_INDEX_BUFFER: usageFlags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT; break;
    case GN_UNIFORM_BUFFER: usageFlags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT; break;
    case GN_STORAGE_BUFFER: usageFlags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT; break;
    }
    return usageFlags;
}

uint32_t VkMemoryIndex(VkPhysicalDevice device, uint32_t memoryType, VkMemoryPropertyFlags flags, gnBool* foundMemory) {
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
        if ((memoryType & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & flags) == flags) {
            *foundMemory = GN_TRUE;
            return i;
        }
    } // this whole thing was adapted from vulkan-tutorial.com
    return 0;
}
gnReturnCode VkCreateBuffer(
    VkGryphnBuffer* buffer, size_t size, gnDevice device,
    VkMemoryPropertyFlags flags, VkBufferUsageFlags usage
) {
    VkBufferCreateInfo bufferInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = size,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };

    VkResult created_buffer = vkCreateBuffer(device->outputDevice->device, &bufferInfo, NULL, &buffer->buffer);
    if (created_buffer != VK_SUCCESS)
        return VkResultToGnReturnCode(created_buffer);

    VkMemoryRequirements bufferRequirements;
    vkGetBufferMemoryRequirements(device->outputDevice->device, buffer->buffer, &bufferRequirements);

    gnBool foundMemory = GN_FALSE;
    VkMemoryAllocateInfo memoryAllocateInfo = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = bufferRequirements.size,
        .memoryTypeIndex = VkMemoryIndex(device->outputDevice->physicalDevice, bufferRequirements.memoryTypeBits, flags, &foundMemory)
    };
    if (!foundMemory) return GN_FAILED_TO_ALLOCATE_MEMORY;

    VkResult memoryFound = vkAllocateMemory(device->outputDevice->device, &memoryAllocateInfo, NULL, &buffer->memory);
    if (memoryFound == VK_SUCCESS) vkBindBufferMemory(device->outputDevice->device, buffer->buffer, buffer->memory, 0);
    return VkResultToGnReturnCode(memoryFound);
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
        return VkCreateBuffer(
            &buffer->buffer->buffer,
            info.size, device,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            vkGryphnBufferType(info.type) | VK_BUFFER_USAGE_TRANSFER_DST_BIT
        );
    } else {
        return VkCreateBuffer(
            &buffer->buffer->buffer,
            info.size, device,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            vkGryphnBufferType(info.type)
        );
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
            vkMapMemory(buffer->device->outputDevice->device, stagingBuffer->memory, 0, chunkSize, 0, &bufferData);
            memcpy(bufferData, (char*)data + (dataSize - sizeLeft), chunkSize);
            vkUnmapMemory(buffer->device->outputDevice->device, stagingBuffer->memory);

            VkBufferCopy copyRegion = {
                .srcOffset = 0,
                .dstOffset = offset + (dataSize - sizeLeft),
                .size = chunkSize
            };
            VkCopyBuffer(buffer->device, stagingBuffer->buffer, buffer->buffer->buffer.buffer, copyRegion);
            sizeLeft -= chunkSize;
        }
    } else {
        vkMapMemory(buffer->device->outputDevice->device, buffer->buffer->buffer.memory, 0, dataSize, 0, &bufferData);
        memcpy((char*)bufferData + offset, data, dataSize);
        vkUnmapMemory(buffer->device->outputDevice->device, buffer->buffer->buffer.memory);
    }
}
void* mapBuffer(gnBufferHandle buffer) {
    void* data;
    vkMapMemory(buffer->device->outputDevice->device, buffer->buffer->buffer.memory, 0, buffer->info.size, 0, &data);
    return data;
}

void gnDestroyVulkanBuffer(VkGryphnBuffer* buffer, VkDevice device) {
    vkDestroyBuffer(device, buffer->buffer, NULL);
    vkFreeMemory(device, buffer->memory, NULL);
}

void destroyBuffer(gnBufferHandle buffer) {
    // if (buffer->buffer->useStagingBuffer == gnTrue) gnDestroyVulkanBuffer(&buffer->buffer->stagingBuffer, buffer->device->outputDevice->device);
    gnDestroyVulkanBuffer(&buffer->buffer->buffer, buffer->device->outputDevice->device);
    free(buffer->buffer);
}
