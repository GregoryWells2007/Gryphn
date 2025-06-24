#pragma once
#include "command/command_buffer/gryphn_command_buffer.h"
#include "utils/gryphn_bool.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformCommandBuffer_t {
    VkCommandBuffer buffer;

    gnBool changedBuffer;
    gnBufferHandle boundIndexBuffer;
    gnGraphicsPipeline boundGraphicsPipeline;
} gnPlatformCommandBuffer;

VkCommandBuffer VkBeginTransferOperation(VkDevice device, VkCommandPool pool);
void VkEndTransferOperation(VkCommandBuffer transferBuffer, VkCommandPool pool, VkQueue syncQueue, VkDevice device);


gnReturnCode allocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPool pool);
gnReturnCode beginCommandBuffer(gnCommandBufferHandle commandBuffer);
void resetCommandBuffer(gnCommandBufferHandle commandBuffer);
gnReturnCode endCommandBuffer(gnCommandBufferHandle commandBuffer);
