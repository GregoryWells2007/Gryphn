#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "core/src/gryphn_handles.h"

typedef struct gnSyncExtFunctions {
    gnReturnCode (*_gnPresentationQueueGetImageAsync)(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex);

    gnReturnCode (*_gnCreateSemaphore)(gnSemaphoreHandle semaphore, gnOutputDeviceHandle device);
    void (*_gnDestroySemaphore)(gnSemaphoreHandle semaphore);


    gnReturnCode (*_gnCreateFence)(gnFenceHandle fence, gnOutputDeviceHandle device);
    void (*_gnWaitForFence)(gnFenceHandle fence, uint64_t timeout);
    void (*_gnResetFence)(gnFenceHandle fence);
    void (*_gnDestroyFence)(gnFenceHandle fence);
} gnSyncExtFunctions;
