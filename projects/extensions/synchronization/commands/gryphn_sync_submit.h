#pragma once
#include "stdint.h"
#include "core/src/renderpass/gryphn_render_pass_descriptor.h"
#include "core/src/gryphn_handles.h"

typedef struct gnSubmitSyncInfo {
    uint32_t waitCount;
    gnRenderPassStage* waitStages;
    gnSemaphoreHandle* waitSemaphores;
    uint32_t signalCount;
    gnSemaphoreHandle* signalSemaphores;
    uint32_t commandBufferCount;
    gnCommandBufferHandle* commandBuffers;
    uint32_t queueIndex;
    gnFenceHandle fence;
} gnSubmitSyncInfo;

gnReturnCode gnSubmitSync(gnOutputDevice device, gnSubmitSyncInfo info);
