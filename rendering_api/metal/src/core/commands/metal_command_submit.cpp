#include "core/commands/submit_command/gryphn_command_submit.h"
#include "core/sync_objects/metal_semaphore.h"
#include "core/commands/metal_command_buffer.h"
#include <Metal/Metal.hpp>

GN_EXPORT gnPresentationQueueState gnCommandSubmitGetValidPresentationQueueFn(gnCommandSubmitData& presentCommandData) {
    return GN_VALID;
}
GN_EXPORT gnErrorCode gnCommandSubmitFn(gnCommandSubmitData& data, const gnFence& fence) {
    dispatch_semaphore_wait(data.waitSemaphore->semaphore->semaphore, DISPATCH_TIME_FOREVER);

    __block dispatch_semaphore_t semToSignal = data.signalSemaphore->semaphore->semaphore;
    data.commandBuffer->commandBuffer->commandBuffer->addCompletedHandler(^void(MTL::CommandBuffer* buffer) {
        dispatch_semaphore_signal(semToSignal);
    });
    data.commandBuffer->commandBuffer->commandBuffer->commit();

    return GN_SUCCESS;
}
