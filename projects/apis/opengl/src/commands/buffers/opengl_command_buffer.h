#pragma once
#include "core/src/command/command_buffer/gryphn_command_buffer.h"

typedef struct gnPlatformCommandBuffer_t {

} gnPlatformCommandBuffer;
gnReturnCode openglCommandPoolAllocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool);
