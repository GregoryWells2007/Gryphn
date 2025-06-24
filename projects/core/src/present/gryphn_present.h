#pragma once
#include "utils/gryphn_error_code.h"
#include "stdint.h"
#include "gryphn_handles.h"

typedef struct gnPresentInfo {
    uint32_t waitCount;
    gnSemaphoreHandle* waitSemaphores;
    uint32_t presentationQueueCount;
    gnPresentationQueueHandle* presentationQueues;
    uint32_t* imageIndices;
    uint32_t queueIndex;
} gnPresentInfo;

gnReturnCode gnPresent(gnOutputDeviceHandle device, gnPresentInfo info);
