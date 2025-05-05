#include <gryphn/gryphn.h>
#include <vulkan/vulkan.h>
#include "core/buffers/gryphn_buffer.h"
#include "output_device/vulkan_output_devices.h"
#include "vulkan_buffers.h"
#include "commands/vulkan_command_buffer.h"

gnReturnCode findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties, uint32_t* memoryType) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            *memoryType = i;
            return GN_SUCCESS;
        }
    }

    return GN_FAILED;
}

void vkCopyBuffer(const gnOutputDevice& outputDevice, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(outputDevice);

    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0; // Optional
    copyRegion.dstOffset = 0; // Optional
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    endSingleTimeCommands(commandBuffer, outputDevice);
}

gnReturnCode vulkanCreateBuffer(const gnOutputDevice& outputDevice, gnSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(outputDevice.outputDevice->device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        return GN_FAILED;
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(outputDevice.outputDevice->device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    uint32_t memoryTypeIndex;
    if (findMemoryType(
        outputDevice.physicalOutputDevice->physicalOutputDevice->device,
        memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        &memoryTypeIndex) != GN_SUCCESS) {
            return GN_FAILED;
    }
    allocInfo.memoryTypeIndex = memoryTypeIndex;

    if (vkAllocateMemory(outputDevice.outputDevice->device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        return GN_FAILED;
    }

    vkBindBufferMemory(outputDevice.outputDevice->device, buffer, bufferMemory, 0);

    return GN_SUCCESS;
}

GN_EXPORT gnReturnCode gnCreateBufferFn(gnBuffer* buffer, const gnOutputDevice& outputDevice) {
    if (buffer->buffer == nullptr) buffer->buffer = new gnPlatformBuffer();
    buffer->buffer->device = const_cast<gnOutputDevice*>(&outputDevice);

    vulkanCreateBuffer(
        *buffer->buffer->device, buffer->size,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        buffer->buffer->stagingBuffer, buffer->buffer->stagingBufferMemory
    );

    if (buffer->bufferType == GN_VERTEX_BUFFER) {
        return vulkanCreateBuffer(
                outputDevice, buffer->size,
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                buffer->buffer->buffer, buffer->buffer->bufferMemory
        );
    } else if (buffer->bufferType == GN_INDEX_BUFFER) {
        return vulkanCreateBuffer(
                outputDevice, buffer->size,
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                buffer->buffer->buffer, buffer->buffer->bufferMemory
        );
    } else if (buffer->bufferType == GN_UNIFORM_BUFFER) {
        return vulkanCreateBuffer(
                outputDevice, buffer->size,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                buffer->buffer->buffer, buffer->buffer->bufferMemory
        );
    }

    return GN_FAILED;
}

GN_EXPORT void gnBufferDataFn(const gnBuffer& buffer, void* inputData) {

    // fuck ass old method idk why this wouldnt work
    // void* data2;
    // vkMapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->bufferMemory, 0, buffer.size, 0, &data2);
    // memcpy(data2, data, buffer.size);
    // vkUnmapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->bufferMemory);

    void* data;
    vkMapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->stagingBufferMemory, 0, buffer.size, 0, &data);
        memcpy(data, inputData, buffer.size);
    vkUnmapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->stagingBufferMemory);

    //const gnOutputDevice& outputDevice, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size
    vkCopyBuffer(*buffer.buffer->device, buffer.buffer->stagingBuffer, buffer.buffer->buffer, buffer.size);

}

GN_EXPORT void gnBufferSubDataFn(const gnBuffer& buffer, gnSize offset, gnSize size, void* inputData) {
    void* data;
    vkMapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->bufferMemory, 0, buffer.size, 0, &data);
    memcpy((char*)data + offset, inputData, size);
    vkUnmapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->bufferMemory);

    // void* data;
    // vkMapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->stagingBufferMemory, 0, buffer.size, 0, &data);
    //     memcpy((char*)data + offset, inputData, size);
    // vkUnmapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->stagingBufferMemory);

    // //const gnOutputDevice& outputDevice, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size
    // vkCopyBuffer(*buffer.buffer->device, buffer.buffer->stagingBuffer, buffer.buffer->buffer, buffer.size);
}
GN_EXPORT void gnBufferClearDataFn(const gnBuffer& buffer) {
    void* data;
    vkMapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->bufferMemory, 0, buffer.size, 0, &data);
    memset(data, 0, buffer.size);
    vkUnmapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->bufferMemory);

    // void* data;
    // vkMapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->stagingBufferMemory, 0, buffer.size, 0, &data);
    //     memset(data, 0, buffer.size);
    // vkUnmapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->stagingBufferMemory);

    // //const gnOutputDevice& outputDevice, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size
    // vkCopyBuffer(*buffer.buffer->device, buffer.buffer->stagingBuffer, buffer.buffer->buffer, buffer.size);
}
GN_EXPORT void gnBufferMapDataFn(const gnBuffer& buffer, void** data) {
    vkMapMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->bufferMemory, 0, buffer.size, 0, data);
}
GN_EXPORT void gnDestroyBufferFn(const gnBuffer& buffer) {
    vkDestroyBuffer(buffer.buffer->device->outputDevice->device, buffer.buffer->buffer, nullptr);
    vkFreeMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->bufferMemory, nullptr);

    vkDestroyBuffer(buffer.buffer->device->outputDevice->device, buffer.buffer->stagingBuffer, nullptr);
    vkFreeMemory(buffer.buffer->device->outputDevice->device, buffer.buffer->stagingBufferMemory, nullptr);
}
