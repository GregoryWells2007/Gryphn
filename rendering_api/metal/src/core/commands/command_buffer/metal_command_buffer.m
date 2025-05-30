#include "metal_command_buffer.h"
#include "core/commands/command_pool/metal_command_pool.h"
#import <Metal/Metal.h>

gnReturnCode gnCommandPoolAllocateCommandBuffersFn(struct gnCommandBuffer_t* commandBuffers, uint32_t count, struct gnCommandPool_t* pool) {
    for (int i = 0; i < count; i++) {
        commandBuffers[i].commandBuffer = malloc(sizeof(gnPlatformCommandBuffer));
        commandBuffers[i].commandBuffer->commandBuffer = [pool->commandPool->commandQueue commandBuffer];
    }

    return GN_SUCCESS;
}

gnReturnCode gnBeginCommandBuffer(struct gnCommandBuffer_t* commandBuffer) {
    commandBuffer->commandBuffer->boundGraphcisPipeline = NULL;
    return GN_SUCCESS;
}

gnReturnCode gnEndCommandBuffer(struct gnCommandBuffer_t* commandBuffer) {
    return GN_SUCCESS;
}
