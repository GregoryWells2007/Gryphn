#pragma once
#include "stdint.h"
#include "core/gryphn_return_code.h"
#include "gryphn_handles.h"

typedef struct gnPresentInfo {
    uint32_t presentationQueueCount;
    gnPresentationQueueHandle* presentationQueues;
    uint32_t* imageIndices;
    // uint32_t queueIndex;
} gnPresentInfo;

gnReturnCode gnPresent(gnOutputDeviceHandle device, gnPresentInfo info);
