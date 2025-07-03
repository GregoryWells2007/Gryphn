#include "vulkan_buffer.h"
#include "buffers/gryphn_buffer.h"
#include "output_device/gryphn_output_device.h"
#include "output_device/vulkan_output_devices.h"
#include "output_device/vulkan_physical_device.h"
#include "commands/command_buffer/vulkan_command_buffer.h"

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
            *foundMemory = gnTrue;
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

    if (vkCreateBuffer(device->outputDevice->device, &bufferInfo, NULL, &buffer->buffer) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_BUFFER;

    VkMemoryRequirements bufferRequirements;
    vkGetBufferMemoryRequirements(device->outputDevice->device, buffer->buffer, &bufferRequirements);

    gnBool foundMemory = gnFalse;
    VkMemoryAllocateInfo memoryAllocateInfo = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = bufferRequirements.size,
        .memoryTypeIndex = VkMemoryIndex(device->physicalDevice.physicalDevice->device, bufferRequirements.memoryTypeBits, flags, &foundMemory)
    };
    if (!foundMemory) return GN_FAILED_TO_ALLOCATE_MEMORY;

    if (vkAllocateMemory(device->outputDevice->device, &memoryAllocateInfo, NULL, &buffer->memory) != VK_SUCCESS)
        return GN_FAILED_TO_ALLOCATE_MEMORY;
    vkBindBufferMemory(device->outputDevice->device, buffer->buffer, buffer->memory, 0);
    return GN_SUCCESS;
}

void VkCopyBuffer(VkBuffer source, VkBuffer destination, size_t size, VkCommandPool pool, VkDevice device, VkQueue queue) {
    VkCommandBuffer transferBuffer = VkBeginTransferOperation(device, pool);
    VkBufferCopy copyRegion = {
      .size = size
    };
    vkCmdCopyBuffer(transferBuffer, source, destination, 1, &copyRegion);
    VkEndTransferOperation(transferBuffer, pool, queue, device);
}

gnReturnCode createBuffer(gnBufferHandle buffer, gnOutputDeviceHandle device, gnBufferInfo info) {
    buffer->buffer = malloc(sizeof(struct gnPlatformBuffer_t));
    VkBufferUsageFlags usage = vkGryphnBufferType(info.type);
    buffer->buffer->useStagingBuffer = gnFalse;
    if (info.usage == GN_STATIC_DRAW) {
        buffer->buffer->useStagingBuffer = gnTrue;
        VkCreateBuffer(
            &buffer->buffer->stagingBuffer,
            info.size, device,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT
        );

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
void bufferData(gnBufferHandle buffer, size_t dataSize, void* data) {
    void* bufferData;
    if (buffer->buffer->useStagingBuffer) {
        vkMapMemory(buffer->device->outputDevice->device, buffer->buffer->stagingBuffer.memory, 0, dataSize, 0, &bufferData);
        memcpy(bufferData, data, dataSize);
        vkUnmapMemory(buffer->device->outputDevice->device, buffer->buffer->stagingBuffer.memory);
        VkCopyBuffer(
            buffer->buffer->stagingBuffer.buffer, buffer->buffer->buffer.buffer, dataSize,
            buffer->device->outputDevice->transferCommandPool, buffer->device->outputDevice->device,
            buffer->device->outputDevice->transferQueue);
    } else {
        vkMapMemory(buffer->device->outputDevice->device, buffer->buffer->buffer.memory, 0, dataSize, 0, &bufferData);
        memcpy(bufferData, data, dataSize);
        vkUnmapMemory(buffer->device->outputDevice->device, buffer->buffer->buffer.memory);
    }
}
void vulkanBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, void* data) {
    void* bufferData;
    if (buffer->buffer->useStagingBuffer) {
        vkMapMemory(buffer->device->outputDevice->device, buffer->buffer->stagingBuffer.memory, 0, dataSize, 0, &bufferData);
        memcpy(bufferData + offset, data, dataSize);
        vkUnmapMemory(buffer->device->outputDevice->device, buffer->buffer->stagingBuffer.memory);
        VkCopyBuffer(
            buffer->buffer->stagingBuffer.buffer, buffer->buffer->buffer.buffer, dataSize,
            buffer->device->outputDevice->transferCommandPool, buffer->device->outputDevice->device,
            buffer->device->outputDevice->transferQueue);
    } else {
        vkMapMemory(buffer->device->outputDevice->device, buffer->buffer->buffer.memory, 0, dataSize, 0, &bufferData);
        memcpy(bufferData + offset, data, dataSize);
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
    if (buffer->buffer->useStagingBuffer == gnTrue) gnDestroyVulkanBuffer(&buffer->buffer->stagingBuffer, buffer->device->outputDevice->device);
    gnDestroyVulkanBuffer(&buffer->buffer->buffer, buffer->device->outputDevice->device);
    free(buffer->buffer);
}
