#include "opengl_command_buffer.h"
#include "commands/pool/opengl_command_pool.h"

gnReturnCode openglCommandPoolAllocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool) {
    for (int i = 0; i < count; i++) {
        gnBool wasAbleToAllocate = GN_FALSE;
        for (int c = i; c < pool->commandPool->allocatedCommandBufferCount; c++) {
            if (pool->commandPool->canBeReallocated[c] == GN_TRUE) {
                pool->commandPool->canBeReallocated[c] = GN_FALSE;
                commandBuffers[i]->commandBuffer = &pool->commandPool->commandBuffers[c];
                commandBuffers[i]->commandBuffer->commmandRunner = openglCreateCommandRunner();

                // glGenBuffers(1, &commandBuffers[i]->commandBuffer->vertexBuffer);
                // glBindBuffer(GL_ARRAY_BUFFER, commandBuffers[i]->commandBuffer->vertexBuffer);
                // glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

                // gl

                // glGenBuffers(1, &commandBuffers[i]->commandBuffer->indexBuffer);

                wasAbleToAllocate = GN_TRUE;
                break;
            }
        }

        if (!wasAbleToAllocate) {
            openglResizeCommandPool(pool);
        }
    }

    return GN_SUCCESS;
}

void openglResetCommandBuffer(gnCommandBuffer commandBuffer) { /* nothing, for now command buffers are implictly reset on begin */ }
gnReturnCode openglBeginCommandBuffer(gnCommandBuffer commandBuffer) {
    openglResetCommandRunner(commandBuffer->commandBuffer->commmandRunner);
    return GN_SUCCESS;
}
gnReturnCode openglEndCommandBuffer(gnCommandBuffer commandBuffer) {
    return GN_SUCCESS;
}
void openglDestroyCommandBuffer(gnCommandBuffer commandBuffer) {
    commandBuffer->commandPool->commandPool->canBeReallocated[commandBuffer->commandBuffer->index] = GN_TRUE;
    openglDestroyCommandRunner(&commandBuffer->commandBuffer->commmandRunner);
}
