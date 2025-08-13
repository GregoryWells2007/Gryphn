#include "opengl_command_pool.h"
#include "stdlib.h"

gnReturnCode openglCreateCommandPool(gnCommandPool commandPool, gnDevice device, gnCommandPoolInfo info) {
    commandPool->commandPool = malloc(sizeof(gnPlatformCommandPool));

    uint32_t baseCommandBufferCount = 10;
    commandPool->commandPool->allocatedCommandBufferCount = baseCommandBufferCount;
    commandPool->commandPool->commandBuffers = malloc(sizeof(gnPlatformCommandBuffer) * baseCommandBufferCount);
    commandPool->commandPool->canBeReallocated = malloc(sizeof(gnBool) * baseCommandBufferCount);

    for (int i = 0; i < baseCommandBufferCount; i++) {
        commandPool->commandPool->commandBuffers[i].index = i;
        commandPool->commandPool->canBeReallocated[i] = GN_TRUE;
    }

    return GN_SUCCESS;
}
void openglDestroyCommandPool(gnCommandPool commandPool) {
    commandPool->commandPool->allocatedCommandBufferCount = 0;
    free(commandPool->commandPool->commandBuffers);
    free(commandPool->commandPool->canBeReallocated);
    free(commandPool->commandPool);
}


void openglResizeCommandPool(gnCommandPoolHandle pool) {
    pool->commandPool->allocatedCommandBufferCount *= 2;
    pool->commandPool->commandBuffers = realloc(pool->commandPool->commandBuffers, sizeof(gnPlatformCommandBuffer) * pool->commandPool->allocatedCommandBufferCount);
    pool->commandPool->canBeReallocated = realloc(pool->commandPool->canBeReallocated, sizeof(gnBool) * pool->commandPool->allocatedCommandBufferCount);
}
