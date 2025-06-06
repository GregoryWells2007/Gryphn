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
    VkMemoryPropertyFlags flags
) {
    VkBufferCreateInfo bufferInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = info.size,
        .usage = vkGryphnBufferType(info.type),
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

gnReturnCode gnCreateBufferFn(gnBufferHandle buffer, gnOutputDeviceHandle device, gnBufferInfo info) {
    buffer->buffer = malloc(sizeof(struct gnPlatformBuffer_t));
    gnReturnCode createdBuffer = VkCreateBuffer(
        &buffer->buffer->buffer, &buffer->buffer->bufferMemory,
        info, device->outputDevice->device, device->physicalDevice.physicalDevice->device,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
    );

    if (info.usage == GN_STATIC_DRAW) {
        gnReturnCode createdBuffer = VkCreateBuffer(
            &buffer->buffer->stagingBuffer, &buffer->buffer->stagingBufferMemory,
            info, device->outputDevice->device, device->physicalDevice.physicalDevice->device,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
        );
        buffer->buffer->useStagingBuffer = gnTrue;
    }

    return GN_SUCCESS;
}
void gnBufferDataFn(gnBufferHandle buffer, size_t dataSize, void* data) {
    void* bufferData;
    vkMapMemory(buffer->device->outputDevice->device, buffer->buffer->bufferMemory, 0, dataSize, 0, &bufferData);
    memcpy(bufferData, data, dataSize);
    vkUnmapMemory(buffer->device->outputDevice->device, buffer->buffer->bufferMemory);
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
