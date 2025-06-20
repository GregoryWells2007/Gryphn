#pragma once
#include <vulkan/vulkan.h>
#include <core/output_device/gryphn_output_device.h>

typedef struct gnPlatformOutputDevice_t {
    VkDevice device;
    uint32_t queueCount;
    VkQueue* queues;

    VkQueue transferQueue;
    VkCommandPool transferCommandPool;

    gnBool enabledOversizedDescriptorPools;
} gnPlatformOutputDevice;

VkCommandBuffer gnBeginVulkanTransferOperation(gnDevice device);
void gnEndVulkanTransferOperation(gnDevice device, VkCommandBuffer commandBuffer);
