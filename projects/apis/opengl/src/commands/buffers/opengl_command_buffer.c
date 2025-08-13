#include "opengl_command_buffer.h"
#include "commands/pool/opengl_command_pool.h"

gnReturnCode openglCommandPoolAllocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool) {
    for (int i = 0; i < count; i++) {
        gnBool wasAbleToAllocate = GN_FALSE;
        for (int c = i; c < pool->commandPool->allocatedCommandBufferCount; c++) {
            if (pool->commandPool->canBeReallocated[c] == GN_TRUE) {
                pool->commandPool->canBeReallocated[c] = GN_FALSE;
                commandBuffers[i]->commandBuffer = &pool->commandPool->commandBuffers[c];
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
