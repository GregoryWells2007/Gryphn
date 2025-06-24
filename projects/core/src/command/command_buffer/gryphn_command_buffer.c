#include "gryphn_command_buffer.h"
#include "command/command_pool/gryphn_command_pool.h"

gnReturnCode gnCommandPoolAllocateCommandBuffersFromPointer(gnCommandBufferHandle* buffers, uint32_t count, gnCommandPoolHandle commandPool) {
    for (int i = 0; i < count; i++) {
        buffers[i] = malloc(sizeof(struct gnCommandBuffer_t));
        buffers[i]->commandPool = commandPool;
    }
    return commandPool->commandFunctions->_gnCommandPoolAllocateCommandBuffers(buffers, count, commandPool);
}

gnReturnCode gnCommandPoolAllocateCommandBuffersFromList(gnCommandBufferArrayList buffers, uint32_t count, gnCommandPoolHandle commandPool) {
    for (int i = 0; i < count; i++) {
        buffers.data[i] = malloc(sizeof(struct gnCommandBuffer_t));
        buffers.data[i]->commandPool = commandPool;
    }
    return gnCommandPoolAllocateCommandBuffersFromPointer(buffers.data, count, commandPool);
}

void gnResetCommandBuffer(gnCommandBufferHandle commandBuffer) {
    commandBuffer->commandPool->commandFunctions->_gnResetCommandBuffer(commandBuffer);
}

gnReturnCode gnBeginCommandBuffer(gnCommandBufferHandle commandBuffer) {
    return commandBuffer->commandPool->commandFunctions->_gnBeginCommandBuffer(commandBuffer);
}

gnReturnCode gnEndCommandBuffer(gnCommandBufferHandle commandBuffer) {
    return commandBuffer->commandPool->commandFunctions->_gnEndCommandBuffer(commandBuffer);
}
