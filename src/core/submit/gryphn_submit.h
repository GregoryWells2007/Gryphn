#pragma once
#include "stdint.h"
#include "core/sync/semaphore/gryphn_semaphore.h"
#include "core/sync/fence/gryphn_fence.h"
#include "core/output_device/gryphn_output_device.h"

typedef struct gnSubmitInfo_t {
    uint32_t waitCount;
    enum gnRenderPassStage_e* waitStages;
    struct gnSemaphore_t* waitSemaphores;
    uint32_t signalCount;
    struct gnSemaphore_t* signalSemaphores;
    uint32_t commandBufferCount;
    gnCommandBufferHandle* commandBuffers;
    uint32_t queueIndex;
    struct gnFence_t* fence;
} gnSubmitInfo;

gnReturnCode gnSubmit(struct gnOutputDevice_t* device, struct gnSubmitInfo_t submit);
