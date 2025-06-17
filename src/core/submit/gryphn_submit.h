#pragma once
#include "stdint.h"
#include "core/renderpass/gryphn_render_pass_descriptor.h"
#include "core/gryphn_handles.h"

typedef struct gnSubmitInfo_t {
    uint32_t waitCount;
    gnRenderPassStage* waitStages;
    gnSemaphoreHandle* waitSemaphores;
    uint32_t signalCount;
    gnSemaphoreHandle* signalSemaphores;
    uint32_t commandBufferCount;
    gnCommandBufferHandle* commandBuffers;
    uint32_t queueIndex;
    gnFenceHandle fence;
} gnSubmitInfo;

gnReturnCode gnSubmit(gnOutputDevice device, gnSubmitInfo info);
