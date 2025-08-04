#include "gryphn_command_buffer.h"
#include "command/command_pool/gryphn_command_pool.h"
#include "instance/gryphn_instance.h"

#include "stdio.h"

gnReturnCode gnCommandPoolAllocateCommandBuffersFromPointer(gnCommandBufferHandle* buffers, uint32_t count, gnCommandPoolHandle commandPool) {
    for (uint32_t i = 0; i < count; i++) {
        buffers[i] = malloc(sizeof(struct gnCommandBuffer_t));
        buffers[i]->commandPool = commandPool;
        buffers[i]->instance = commandPool->instance;
    }
    return commandPool->instance->callingLayer->commandFunctions._gnCommandPoolAllocateCommandBuffers(buffers, count, commandPool);
}

gnReturnCode gnCommandPoolAllocateCommandBuffersFromList(gnCommandBufferArrayList buffers, uint32_t count, gnCommandPoolHandle commandPool) {
    gnCommandBufferHandle* buffersArray = malloc(sizeof(gnCommandBufferHandle) * count);
    gnReturnCode code = gnCommandPoolAllocateCommandBuffersFromPointer(buffersArray, count, commandPool);
    for (uint32_t i = 0; i < count; i++)
        gnCommandBufferArrayListAdd(buffers, buffersArray[i]);
    return code;
}

void gnResetCommandBuffer(gnCommandBufferHandle commandBuffer) {
    commandBuffer->commandPool->instance->callingLayer->commandFunctions._gnResetCommandBuffer(commandBuffer);
}

gnReturnCode gnBeginCommandBuffer(gnCommandBufferHandle commandBuffer) {
    return commandBuffer->commandPool->instance->callingLayer->commandFunctions._gnBeginCommandBuffer(commandBuffer);
}

gnReturnCode gnEndCommandBuffer(gnCommandBufferHandle commandBuffer) {
    return commandBuffer->commandPool->instance->callingLayer->commandFunctions._gnEndCommandBuffer(commandBuffer);
}

void gnDestroyCommandBuffer(gnCommandBufferHandle commandBuffer) {
    commandBuffer->commandPool->instance->callingLayer->commandFunctions._gnDestroyCommandBuffer(commandBuffer);
}


GN_ARRAY_LIST_DEFINITION(gnCommandBuffer)
