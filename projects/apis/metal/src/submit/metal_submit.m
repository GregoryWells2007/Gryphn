#include "submit/gryphn_submit.h"
#include "sync/semaphore/metal_semaphore.h"
#include "commands/command_buffer/metal_command_buffer.h"
#include "debugger/gryphn_debugger.h"
#include "commands/command_pool/metal_command_pool.h"
#include "sync/fence/gryphn_fence.h"

gnReturnCode gnSubmitFn(gnDevice* device, gnSubmitInfo info) {
    for (int i = 0; i < info.waitCount; i++) {
        while (!info.waitSemaphores[i]->semaphore->eventTriggered) {}
    }


    __block gnSemaphore* semsToSignal = info.signalSemaphores;
    __block int semsToSignalCount = info.signalCount;
    __block gnFence fenceToSignal = info.fence;

    for (int i = 0; i < info.commandBufferCount; i++) {
        id<MTLCommandBuffer> commandBuffer = info.commandBuffers[i]->commandBuffer->commandBuffer;
        [info.commandBuffers[i]->commandBuffer->commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
            for (int c = 0; c < semsToSignalCount; c++) {
                semsToSignal[c]->semaphore->eventTriggered = gnTrue;
            }
        }];
        fenceToSignal->signaled = gnTrue;

        [commandBuffer commit];
    }

    return GN_SUCCESS;
}
