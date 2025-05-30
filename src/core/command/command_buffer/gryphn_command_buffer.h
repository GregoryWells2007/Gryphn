#pragma once
#include <core/command/command_pool/gryphn_command_pool.h>

typedef struct gnCommandBuffer_t {
    struct gnPlatformCommandBuffer_t* commandBuffer;
    struct gnCommandPool_t* commandPool;
} gnCommandBuffer;

gnReturnCode gnCommandPoolAllocateCommandBuffers(struct gnCommandBuffer_t* buffers, uint32_t count, struct gnCommandPool_t* commandPool);

gnReturnCode gnBeginCommandBuffer(struct gnCommandBuffer_t* commandBuffer);
gnReturnCode gnEndCommandBuffer(struct gnCommandBuffer_t* commandBuffer);
