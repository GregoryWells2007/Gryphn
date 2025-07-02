#include "vulkan_command_buffer.h"
#include "commands/command_pool/vulkan_command_pool.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode allocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPool pool) {
    VkCommandBufferAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = pool->commandPool->commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = count,
    };

    VkCommandBuffer* buffers = malloc(sizeof(VkCommandBuffer) * count);

    if (vkAllocateCommandBuffers(pool->device->outputDevice->device, &allocInfo, buffers) != VK_SUCCESS)
        return GN_FAILED_TO_ALLOCATE_COMMAND_BUFFERS;

    for (int i = 0; i < count; i++) {
        commandBuffers[i]->commandBuffer = malloc(sizeof(gnPlatformCommandBuffer));
        commandBuffers[i]->commandBuffer->buffer = buffers[i];
    }

    return GN_SUCCESS;
}

void resetCommandBuffer(gnCommandBufferHandle commandBuffer) {
    vkResetCommandBuffer(commandBuffer->commandBuffer->buffer, 0);
}


gnReturnCode beginCommandBuffer(gnCommandBufferHandle commandBuffer) {
    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO
    };

    if (vkBeginCommandBuffer(commandBuffer->commandBuffer->buffer, &beginInfo) != VK_SUCCESS) {
        return GN_FAILED_TO_BEGIN_RECORDING;
    }
    return GN_SUCCESS;
}

gnReturnCode endCommandBuffer(gnCommandBufferHandle commandBuffer) {
    if (vkEndCommandBuffer(commandBuffer->commandBuffer->buffer) != VK_SUCCESS)
        return GN_FAIELD_TO_END_RECORDING;
    return GN_SUCCESS;
}


VkCommandBuffer VkBeginTransferOperation(VkDevice device, VkCommandPool pool) {
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
    return commandBuffer;
}

void VkEndTransferOperation(VkCommandBuffer transferBuffer, VkCommandPool pool, VkQueue syncQueue, VkDevice device) {
    vkEndCommandBuffer(transferBuffer);

    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .commandBufferCount = 1,
        .pCommandBuffers = &transferBuffer
    };

    vkQueueSubmit(syncQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(syncQueue);
    vkFreeCommandBuffers(device, pool, 1, &transferBuffer);
}

void destroyVulkanCommandBuffer(gnCommandBufferHandle commandBuffer) {
    vkFreeCommandBuffers(commandBuffer->commandPool->device->outputDevice->device, commandBuffer->commandPool->commandPool->commandPool, 1, &commandBuffer->commandBuffer->buffer);
}
