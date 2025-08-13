#pragma once
#include "core/src/command/command_buffer/gryphn_command_buffer.h"

typedef struct gnPlatformCommandBuffer_t {
    int index;
} gnPlatformCommandBuffer;
gnReturnCode openglCommandPoolAllocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool);

void openglResetCommandBuffer(gnCommandBuffer commandBuffer);
gnReturnCode openglBeginCommandBuffer(gnCommandBuffer commandBuffer);
gnReturnCode openglEndCommandBuffer(gnCommandBuffer commandBuffer);
void openglDestroyCommandBuffer(gnCommandBuffer commandBuffer);
