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

gnReturnCode gnCreateBufferFn(gnBufferHandle buffer, gnOutputDeviceHandle device, gnBufferInfo info) {
    buffer->buffer = malloc(sizeof(struct gnPlatformBuffer_t));
    VkBufferCreateInfo bufferInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = info.size,
        .usage = vkGryphnBufferType(info.type),
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };

    if (vkCreateBuffer(device->outputDevice->device, &bufferInfo, NULL, &buffer->buffer->buffer) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_BUFFER;

    VkMemoryRequirements bufferRequirements;
    vkGetBufferMemoryRequirements(device->outputDevice->device, buffer->buffer->buffer, &bufferRequirements);

    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(device->physicalDevice.physicalDevice->device, &memoryProperties);

    VkMemoryAllocateInfo memoryAllocateInfo = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = bufferRequirements.size,
    };

    gnBool foundMemory = gnFalse;
    VkMemoryPropertyFlagBits flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
        if ((bufferRequirements.memoryTypeBits & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & flags) == flags) {
            memoryAllocateInfo.memoryTypeIndex = i;
            foundMemory = gnTrue;
        }
    } // this whole thing was adapted from vulkan-tutorial.com
    if (!foundMemory) return GN_FAILED_TO_ALLOCATE_MEMORY;

    if (vkAllocateMemory(device->outputDevice->device, &memoryAllocateInfo, NULL, &buffer->buffer->bufferMemory) != VK_SUCCESS) {
        return GN_FAILED_TO_ALLOCATE_MEMORY;
    }
    vkBindBufferMemory(device->outputDevice->device, buffer->buffer->buffer, buffer->buffer->bufferMemory, 0);
    return GN_SUCCESS;
}
void gnDestroyBufferFn(gnBufferHandle buffer) {
    vkDestroyBuffer(buffer->device->outputDevice->device, buffer->buffer->buffer, NULL);
    vkFreeMemory(buffer->device->outputDevice->device, buffer->buffer->bufferMemory, NULL);
    free(buffer->buffer);
}
