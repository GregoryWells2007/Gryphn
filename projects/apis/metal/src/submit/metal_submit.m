#include "metal_submit.h"
#include "synchronization/fence/gryphn_fence.h"

gnReturnCode metalSyncSubmit(gnOutputDevice device, gnSubmitSyncInfo info) {
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
            fenceToSignal->signaled = gnTrue;
        }];

        [commandBuffer commit];
    }

    return GN_SUCCESS;
}

gnReturnCode metalSubmit(gnOutputDevice device, gnSubmitInfo info) {
    for (int i = 0; i < info.commandBufferCount; i++) {
        id<MTLCommandBuffer> commandBuffer = info.commandBuffers[i]->commandBuffer->commandBuffer;
        [commandBuffer commit];
    }

    [info.commandBuffers[info.commandBufferCount - 1]->commandBuffer->commandBuffer waitUntilCompleted];
    return GN_SUCCESS;
}
