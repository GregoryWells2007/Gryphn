#include "vulkan_buffer.h"
#include "core/buffers/gryphn_buffer.h"
#include "core/output_device/gryphn_output_device.h"
#include "output_device/vulkan_output_devices.h"
#include "output_device/vulkan_physical_device.h"

VkBufferUsageFlags vkGryphnBufferType(gnBufferType type) {
switch (type) {
case GN_VERTEX_BUFFER: return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
}
}

gnReturnCode VkCreateBuffer(
    VkBuffer* buffer, VkDeviceMemory* memory, gnBufferInfo info,
    VkDevice device, VkPhysicalDevice physcialDevice,
    VkMemoryPropertyFlags flags, VkBufferUsageFlags usage
) {
    VkBufferCreateInfo bufferInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = info.size,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };

    if (vkCreateBuffer(device, &bufferInfo, NULL, buffer) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_BUFFER;

    VkMemoryRequirements bufferRequirements;
    vkGetBufferMemoryRequirements(device, *buffer, &bufferRequirements);

    VkMemoryAllocateInfo memoryAllocateInfo = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = bufferRequirements.size,
    };

    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(physcialDevice, &memoryProperties);

    gnBool foundMemory = gnFalse;
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
        if ((bufferRequirements.memoryTypeBits & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & flags) == flags) {
            memoryAllocateInfo.memoryTypeIndex = i;
            foundMemory = gnTrue;
        }
    } // this whole thing was adapted from vulkan-tutorial.com
    if (!foundMemory) return GN_FAILED_TO_ALLOCATE_MEMORY;

    if (vkAllocateMemory(device, &memoryAllocateInfo, NULL, memory) != VK_SUCCESS) {
        return GN_FAILED_TO_ALLOCATE_MEMORY;
    }
    vkBindBufferMemory(device, *buffer, *memory, 0);
    return GN_SUCCESS;
}

void VkCopyBuffer(VkBuffer source, VkBuffer destination, size_t size, VkCommandPool pool, VkDevice device, VkQueue queue) {
    VkCommandBufferAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandPool = pool,
        .commandBufferCount = 1
    };

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };
    vkBeginCommandBuffer(commandBuffer, &beginInfo);


    VkBufferCopy copyRegion = {
      .size = size
    };
    vkCmdCopyBuffer(commandBuffer, source, destination, 1, &copyRegion);
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffer
    };

    vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(queue);
}

gnReturnCode gnCreateBufferFn(gnBufferHandle buffer, gnOutputDeviceHandle device, gnBufferInfo info) {
    buffer->buffer = malloc(sizeof(struct gnPlatformBuffer_t));
    VkBufferUsageFlags usage = vkGryphnBufferType(info.type);
    if (info.usage == GN_STATIC_DRAW) {
        gnReturnCode createdBuffer = VkCreateBuffer(
            &buffer->buffer->stagingBuffer, &buffer->buffer->stagingBufferMemory,
            info, device->outputDevice->device, device->physicalDevice.physicalDevice->device,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, VK_BUFFER_USAGE_TRANSFER_SRC_BIT
        );
        usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        buffer->buffer->useStagingBuffer = gnTrue;
    }

    gnReturnCode createdBuffer = VkCreateBuffer(
        &buffer->buffer->buffer, &buffer->buffer->bufferMemory,
        info, device->outputDevice->device, device->physicalDevice.physicalDevice->device,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, usage
    );


    return GN_SUCCESS;
}
void gnBufferDataFn(gnBufferHandle buffer, size_t dataSize, void* data) {
    void* bufferData;
    if (buffer->buffer->useStagingBuffer) {
        vkMapMemory(buffer->device->outputDevice->device, buffer->buffer->stagingBufferMemory, 0, dataSize, 0, &bufferData);
        memcpy(bufferData, data, dataSize);
        vkUnmapMemory(buffer->device->outputDevice->device, buffer->buffer->stagingBufferMemory);
        VkCopyBuffer(
            buffer->buffer->stagingBuffer, buffer->buffer->buffer, dataSize,
            buffer->device->outputDevice->transferCommandPool, buffer->device->outputDevice->device,
            buffer->device->outputDevice->transferQueue);
    } else {
        vkMapMemory(buffer->device->outputDevice->device, buffer->buffer->bufferMemory, 0, dataSize, 0, &bufferData);
        memcpy(bufferData, data, dataSize);
        vkUnmapMemory(buffer->device->outputDevice->device, buffer->buffer->bufferMemory);
    }
}
void gnDestroyBufferFn(gnBufferHandle buffer) {
    if (buffer->buffer->useStagingBuffer == gnTrue) {
        vkDestroyBuffer(buffer->device->outputDevice->device, buffer->buffer->stagingBuffer, NULL);
        vkFreeMemory(buffer->device->outputDevice->device, buffer->buffer->stagingBufferMemory, NULL);
    }

    vkDestroyBuffer(buffer->device->outputDevice->device, buffer->buffer->buffer, NULL);
    vkFreeMemory(buffer->device->outputDevice->device, buffer->buffer->bufferMemory, NULL);
    free(buffer->buffer);
}
