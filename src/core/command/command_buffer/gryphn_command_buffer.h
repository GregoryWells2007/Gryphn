#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "utils/lists/gryphn_array_list.h"
#include "core/gryphn_handles.h"

#ifdef GN_REVEAL_IMPL
struct gnCommandBuffer_t {
    struct gnPlatformCommandBuffer_t* commandBuffer;
    gnCommandPoolHandle commandPool;
};
#endif

GN_ARRAY_LIST(gnCommandBuffer);

gnReturnCode gnCommandPoolAllocateCommandBuffersFromPointer(gnCommandBufferHandle* buffers, uint32_t count, gnCommandPoolHandle commandPool);
// will reserve the space for ${count} number of elements
gnReturnCode gnCommandPoolAllocateCommandBuffersFromList(gnCommandBufferArrayList buffers, uint32_t count, gnCommandPoolHandle commandPool);

#define gnCommandPoolAllocateCommandBuffers(buffers, count, commandPool)       \
    _Generic((buffers),                                                        \
        gnCommandBufferArrayList: gnCommandPoolAllocateCommandBuffersFromList, \
        default: gnCommandPoolAllocateCommandBuffersFromPointer                \
    )(buffers, count, commandPool)

void gnResetCommandBuffer(gnCommandBufferHandle commandBuffer);
gnReturnCode gnBeginCommandBuffer(gnCommandBufferHandle commandBuffer);
gnReturnCode gnEndCommandBuffer(gnCommandBufferHandle commandBuffer);
