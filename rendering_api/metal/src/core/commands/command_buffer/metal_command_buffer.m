#include "metal_command_buffer.h"
#include "core/commands/command_pool/metal_command_pool.h"
#import <Metal/Metal.h>

gnReturnCode gnCommandPoolAllocateCommandBuffersFn(struct gnCommandBuffer_t* commandBuffers, uint32_t count, struct gnCommandPool_t* pool) {
    for (int i = 0; i < count; i++) {
        commandBuffers[i].commandBuffer = malloc(sizeof(gnPlatformCommandBuffer));
    }

    return GN_SUCCESS;
}
void gnResetCommandBufferFn(struct gnCommandBuffer_t *commandBuffer) {
    // do nothing
}
gnReturnCode gnBeginCommandBufferFn(struct gnCommandBuffer_t* commandBuffer) {
    commandBuffer->commandBuffer->boundGraphcisPipeline = NULL;
    commandBuffer->commandBuffer->commandBuffer = [commandBuffer->commandPool->commandPool->commandQueue commandBuffer];
    return GN_SUCCESS;
}

gnReturnCode gnEndCommandBufferFn(struct gnCommandBuffer_t* commandBuffer) {
    // [commandBuffer->commandBuffer->commandBuffer commit];
    return GN_SUCCESS;
}
