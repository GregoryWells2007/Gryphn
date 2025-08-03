#pragma once
#include <vulkan/vulkan.h>
#include <output_device/gryphn_output_device.h>
#include "buffers/vulkan_buffer.h"
#include "vulkan_physical_device.h"

typedef struct vulkanQueue {
    VkQueue queue;
    vulkanNeededQueue queueInfo;
} vulkanQueue;

typedef struct gnPlatformOutputDevice_t {
    VkDevice device;
    VkPhysicalDevice physicalDevice;

    uint32_t transferQueueIndex, graphicsQueueIndex;
    uint32_t queueCount;
    vulkanQueue* queues;

    VkCommandPool transferCommandPool;

    VkGryphnBuffer stagingBuffer;
    VkDeviceSize stagingBufferSize;

    VkFence barrierFence;
    gnBool enabledOversizedDescriptorPools;
} gnPlatformOutputDevice;

VkCommandBuffer gnBeginVulkanTransferOperation(gnDevice device);
void gnEndVulkanTransferOperation(gnDevice device, VkCommandBuffer commandBuffer);


gnReturnCode createVulkanOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle device, gnOutputDeviceInfo deviceInfo);
void waitForDevice(gnOutputDeviceHandle device);
void destroyVulkanOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle device);
