#include "core/submit/gryphn_submit.h"
#include "core/sync/semaphore/metal_semaphore.h"
#include "core/commands/command_buffer/metal_command_buffer.h"
#include "core/debugger/gryphn_debugger.h"
#include "core/commands/command_pool/metal_command_pool.h"

gnReturnCode gnSubmitFn(struct gnOutputDevice_t* device, struct gnSubmitInfo_t info) {
    for (int i = 0; i < info.waitCount; i++) {
        while (!info.waitSemaphores[i].semaphore->eventTriggered) {}
    }


    __block gnSemaphore* semsToSignal = info.signalSemaphores;
    __block int semsToSignalCount = info.signalCount;
    __block gnFence* fenceToSignal = info.fence;

    for (int i = 0; i < info.commandBufferCount; i++) {
        id<MTLCommandBuffer> commandBuffer = info.commandBuffers[i]->commandBuffer->commandBuffer;
        [info.commandBuffers[i]->commandBuffer->commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
            for (int c = 0; c < semsToSignalCount; c++) {
                semsToSignal[c].semaphore->eventTriggered = gnTrue;
            }
        }];
        fenceToSignal->signaled = gnTrue;

        [commandBuffer commit];
    }

    return GN_SUCCESS;
}
