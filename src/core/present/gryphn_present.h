#pragma once
#include "core/sync/semaphore/gryphn_semaphore.h"
#include "core/presentation_queue/gryphn_presentation_queue.h"

typedef struct gnPresentInfo_t {
    uint32_t waitCount;
    struct gnSemaphore_t* waitSemaphores;
    uint32_t presentationQueueCount;
    gnPresentationQueueHandle* presentationQueues;
    uint32_t* imageIndices;
    uint32_t queueIndex;
} gnPresentInfo;

gnReturnCode gnPresent(struct gnOutputDevice_t* device, struct gnPresentInfo_t info);
