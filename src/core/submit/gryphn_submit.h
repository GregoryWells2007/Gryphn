#pragma once
#include "stdint.h"
#include "core/sync/fence/gryphn_fence.h"

typedef struct gnSubmitInfo_t {
    uint32_t waitCount;
    enum gnRenderPassStage_e* waitStages;
    gnSemaphoreHandle* waitSemaphores;
    uint32_t signalCount;
    gnSemaphoreHandle* signalSemaphores;
    uint32_t commandBufferCount;
    gnCommandBufferHandle* commandBuffers;
    uint32_t queueIndex;
    struct gnFence_t* fence;
} gnSubmitInfo;

gnReturnCode gnSubmit(gnOutputDevice device, gnSubmitInfo info);
