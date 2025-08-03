#pragma once
#include "stdint.h"
#include "core/gryphn_return_code.h"
#include "utils/lists/gryphn_array_list.h"
#include "gryphn_handles.h"

#ifdef GN_REVEAL_IMPL
struct gnCommandBuffer_t {
    struct gnPlatformCommandBuffer_t* commandBuffer;
    gnCommandPoolHandle commandPool;
    gnInstance instance;
};
#endif

GN_ARRAY_LIST_HEADER(gnCommandBuffer);

gnReturnCode gnCommandPoolAllocateCommandBuffersFromPointer(gnCommandBufferHandle* buffers, uint32_t count, gnCommandPoolHandle commandPool);
gnReturnCode gnCommandPoolAllocateCommandBuffersFromList(gnCommandBufferArrayList buffers, uint32_t count, gnCommandPoolHandle commandPool);

#define gnCommandPoolAllocateCommandBuffers(buffers, count, commandPool)       \
    _Generic((buffers),                                                        \
        gnCommandBufferArrayList: gnCommandPoolAllocateCommandBuffersFromList, \
        default: gnCommandPoolAllocateCommandBuffersFromPointer                \
    )(buffers, count, commandPool)

void gnResetCommandBuffer(gnCommandBufferHandle commandBuffer);
gnReturnCode gnBeginCommandBuffer(gnCommandBufferHandle commandBuffer);
gnReturnCode gnEndCommandBuffer(gnCommandBufferHandle commandBuffer);
void gnDestroyCommandBuffer(gnCommandBufferHandle commandBuffer);
