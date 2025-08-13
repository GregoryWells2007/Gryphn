#pragma once
#include "core/src/command/command_pool/gryphn_command_pool.h"
#include "commands/buffers/opengl_command_buffer.h"
#include "utils/gryphn_bool.h"

typedef struct gnPlatformCommandPool_t {
    uint32_t allocatedCommandBufferCount;
    gnPlatformCommandBuffer* commandBuffers;
    gnBool* canBeReallocated;
} gnPlatformCommandPool;

gnReturnCode openglCreateCommandPool(gnCommandPool commandPool, gnDevice device, gnCommandPoolInfo info);
void openglDestroyCommandPool(gnCommandPool commandPool);

void openglResizeCommandPool(gnCommandPoolHandle pool);
