#pragma once
#include "stdint.h"
#include "core/gryphn_return_code.h"
#include "gryphn_handles.h"

typedef struct gnSubmitInfo {
    uint32_t commandBufferCount;
    gnCommandBufferHandle* commandBuffers;
} gnSubmitInfo;
gnReturnCode gnSubmit(gnOutputDevice device, gnSubmitInfo info);
