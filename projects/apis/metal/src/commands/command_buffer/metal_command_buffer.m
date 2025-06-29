#include "metal_command_buffer.h"
#include "commands/command_pool/metal_command_pool.h"
#import <Metal/Metal.h>

gnReturnCode allocateMetalCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPool pool) {
    for (int i = 0; i < count; i++) {
        commandBuffers[i]->commandBuffer = malloc(sizeof(gnPlatformCommandBuffer));    }

    return GN_SUCCESS;
}
void resetMetalCommandBuffer(gnCommandBuffer commandBuffer) {
    commandBuffer->commandBuffer->commandBuffer = [commandBuffer->commandPool->commandPool->commandQueue commandBuffer];
}
gnReturnCode beginMetalCommandBuffer(gnCommandBuffer commandBuffer) {
    commandBuffer->commandBuffer->boundGraphcisPipeline = NULL;
    commandBuffer->commandBuffer->encoder = nil;
    return GN_SUCCESS;
}

gnReturnCode endMetalCommandBuffer(gnCommandBuffer commandBuffer) {
    // [commandBuffer->commandBuffer->commandBuffer commit];
    return GN_SUCCESS;
}
