#pragma once
#include "core/src/command/command_buffer/gryphn_command_buffer.h"
#include "commands/commands/opengl_command_runner.h"

typedef struct gnPlatformCommandBuffer_t {
    int index;
    openglCommandRunner commmandRunner;
} gnPlatformCommandBuffer;
gnReturnCode openglCommandPoolAllocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool);

void openglResetCommandBuffer(gnCommandBuffer commandBuffer);
gnReturnCode openglBeginCommandBuffer(gnCommandBuffer commandBuffer);
gnReturnCode openglEndCommandBuffer(gnCommandBuffer commandBuffer);
void openglDestroyCommandBuffer(gnCommandBuffer commandBuffer);
