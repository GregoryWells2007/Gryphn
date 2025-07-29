#include "metal_command_buffer.h"
#include "commands/command_pool/metal_command_pool.h"
#include "instance/gryphn_instance.h"
#import <Metal/Metal.h>

gnReturnCode allocateMetalCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPool pool) {
    for (int i = 0; i < count; i++) {
        commandBuffers[i]->commandBuffer = malloc(sizeof(gnPlatformCommandBuffer));
        commandBuffers[i]->commandBuffer->commandBuffer = [pool->commandPool->commandQueue commandBuffer];

        // write a command log at some point
        if ((pool->info.flags & GN_REUSE_COMMAND_BUFFERS) == GN_REUSE_COMMAND_BUFFERS)
            commandBuffers[i]->commandBuffer->isIndirectCommandBuffer = GN_TRUE;
    }

    return GN_SUCCESS;
}
void resetMetalCommandBuffer(gnCommandBuffer commandBuffer) {
    if (commandBuffer->commandBuffer->isIndirectCommandBuffer)
        commandBuffer->commandBuffer->commandBuffer = [commandBuffer->commandPool->commandPool->commandQueue commandBuffer];
}
gnReturnCode beginMetalCommandBuffer(gnCommandBuffer commandBuffer) {
    commandBuffer->commandBuffer->boundGraphcisPipeline = NULL;
    commandBuffer->commandBuffer->encoder = nil;
    return GN_SUCCESS;
}

gnReturnCode endMetalCommandBuffer(gnCommandBuffer commandBuffer) { return GN_SUCCESS; }

void destroyMetalCommandBuffer(gnCommandBuffer commandBuffer) {
    [commandBuffer->commandBuffer->commandBuffer release];
}
