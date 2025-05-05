#pragma once
#include "vulkan/vulkan.h"
#include "gryphn/gryphn_utils.h"
struct gnOutputDevice;


struct gnPlatformBuffer {
    // normal buffer jazz
    VkBuffer buffer;
    VkDeviceMemory bufferMemory;

    // staging buffer shabang
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    gnOutputDevice* device;
};

gnReturnCode vulkanCreateBuffer(const gnOutputDevice& outputDevice, gnSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
gnReturnCode findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties, uint32_t* memoryType);
