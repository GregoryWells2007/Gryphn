#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/sync_objects/gryphn_sync_semaphore.h"
#include "core/sync_objects/gryphn_fence.h"
#include "core/commands/gryphn_command_buffer.h"
#include "core/presentation_queue/gryphn_present_queue_state.h"

struct gnPlatformCommandSubmitData;

struct gnCommandSubmitData {
ACCESS_LEVEL:
    gnPlatformCommandSubmitData* commandSubmitData = nullptr;

    gnSyncSemaphore *waitSemaphore = nullptr, *signalSemaphore = nullptr;
    gnCommandBuffer* commandBuffer = nullptr;
public:
    gnCommandSubmitData() {}
};

void gnCommandSubmitDataSetWaitSemaphore(gnCommandSubmitData& data, gnSyncSemaphore& semaphore);
void gnCommandSubmitDataSetCommandBuffer(gnCommandSubmitData& data, gnCommandBuffer& commandBuffer);
void gnCommandSubmitDataSetSignalSemaphore(gnCommandSubmitData& data, gnSyncSemaphore& semaphore);
inline gnPresentationQueueState (*gnCommandSubmitGetValidPresentationQueue)(gnCommandSubmitData& presentCommandData);
inline gnErrorCode (*gnCommandSubmit)(gnCommandSubmitData& data, const gnFence& fence);
