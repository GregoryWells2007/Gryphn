#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "gryphn_handles.h"

typedef struct gnSubmitInfo {
    uint32_t commandBufferCount;
    gnCommandBufferHandle* commandBuffers;
    // uint32_t queueIndex;
} gnSubmitInfo;
gnReturnCode gnSubmit(gnOutputDevice device, gnSubmitInfo info);
