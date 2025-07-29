#pragma once
#include "stdint.h"
#include "core/gryphn_return_code.h"
#include "gryphn_handles.h"

typedef struct gnPresentSyncInfo {
    uint32_t waitCount;
    gnSemaphoreHandle* waitSemaphores;
    uint32_t presentationQueueCount;
    gnPresentationQueueHandle* presentationQueues;
    uint32_t* imageIndices;
} gnPresentSyncInfo;

gnReturnCode gnPresentSync(gnOutputDeviceHandle device, gnPresentSyncInfo info);
