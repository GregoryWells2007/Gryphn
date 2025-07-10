#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "gryphn_handles.h"

typedef struct gnPresentSyncInfo {
    uint32_t waitCount;
    gnSemaphoreHandle* waitSemaphores;
    uint32_t presentationQueueCount;
    gnPresentationQueueHandle* presentationQueues;
    uint32_t* imageIndices;
    uint32_t queueIndex;
} gnPresentSyncInfo;

gnReturnCode gnPresentSync(gnOutputDeviceHandle device, gnPresentSyncInfo info);
