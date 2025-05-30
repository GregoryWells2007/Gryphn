#include "vulkan_command_buffer.h"
#include "commands/command_pool/vulkan_command_pool.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode gnCommandPoolAllocateCommandBuffersFn(struct gnCommandBuffer_t* commandBuffers, uint32_t count, struct gnCommandPool_t* pool) {
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
        commandBuffers[i].commandBuffer = malloc(sizeof(gnPlatformCommandBuffer));
        commandBuffers[i].commandBuffer->buffer = buffers[i];
    }

    return GN_SUCCESS;
}

void gnResetCommandBufferFn(struct gnCommandBuffer_t* commandBuffer) {
    vkResetCommandBuffer(commandBuffer->commandBuffer->buffer, 0);
}


gnReturnCode gnBeginCommandBufferFn(struct gnCommandBuffer_t* commandBuffer) {
    VkCommandBufferBeginInfo beginInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO
    };

    if (vkBeginCommandBuffer(commandBuffer->commandBuffer->buffer, &beginInfo) != VK_SUCCESS) {
        return GN_FAILED_TO_BEGIN_RECORDING;
    }
    return GN_SUCCESS;
}

gnReturnCode gnEndCommandBufferFn(struct gnCommandBuffer_t* commandBuffer) {
    if (vkEndCommandBuffer(commandBuffer->commandBuffer->buffer) != VK_SUCCESS)
        return GN_FAIELD_TO_END_RECORDING;
    return GN_SUCCESS;
}
