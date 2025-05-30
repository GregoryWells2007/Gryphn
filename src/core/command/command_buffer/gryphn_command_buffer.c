#include "gryphn_command_buffer.h"
#include "core/gryphn_platform_functions.h"
#include "stdio.h"

gnReturnCode gnCommandPoolAllocateCommandBuffers(struct gnCommandBuffer_t* buffers, uint32_t count, struct gnCommandPool_t* commandPool) {
    for (int i = 0; i < count; i++) {
        buffers[i].commandPool = commandPool;
    }
    return commandPool->commandFunctions->_gnCommandPoolAllocateCommandBuffers(buffers, count, commandPool);
}

void gnResetCommandBuffer(struct gnCommandBuffer_t* commandBuffer) {
    commandBuffer->commandPool->commandFunctions->_gnResetCommandBuffer(commandBuffer);
}

gnReturnCode gnBeginCommandBuffer(struct gnCommandBuffer_t* commandBuffer) {
    return commandBuffer->commandPool->commandFunctions->_gnBeginCommandBuffer(commandBuffer);
}

gnReturnCode gnEndCommandBuffer(struct gnCommandBuffer_t* commandBuffer) {
    return commandBuffer->commandPool->commandFunctions->_gnEndCommandBuffer(commandBuffer);
}
