#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "core/gryphn_handles.h"

#ifdef GN_REVEAL_IMPL
struct gnCommandBuffer_t {
    struct gnPlatformCommandBuffer_t* commandBuffer;
    gnCommandPoolHandle commandPool;
};
#endif

gnReturnCode gnCommandPoolAllocateCommandBuffers(gnCommandBufferHandle* buffers, uint32_t count, gnCommandPoolHandle commandPool);

void gnResetCommandBuffer(gnCommandBufferHandle commandBuffer);
gnReturnCode gnBeginCommandBuffer(gnCommandBufferHandle commandBuffer);
gnReturnCode gnEndCommandBuffer(gnCommandBufferHandle commandBuffer);
