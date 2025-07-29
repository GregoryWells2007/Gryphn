#include "metal_submit.h"
#include "synchronization/fence/gryphn_fence.h"

gnReturnCode metalSyncSubmit(gnOutputDevice device, gnSubmitSyncInfo info) {
    __block gnFence fenceToSignal = info.fence;
    __block atomic_int buffersLeft;
    atomic_init(&buffersLeft, info.commandBufferCount);

    for (int i = 0; i < info.commandBufferCount; i++) {
        id <MTLCommandBuffer> buffer = [info.commandBuffers[i]->commandPool->commandPool->commandQueue commandBuffer];
        for (int c = 0; c < info.waitCount; c++)
            mtlWaitSemaphore(info.waitSemaphores[c], buffer);
        [buffer commit];

        id<MTLCommandBuffer> commandBuffer = info.commandBuffers[i]->commandBuffer->commandBuffer;

        for (int c = 0; c < info.signalCount; c++)
            mtlSignalSemaphore(info.signalSemaphores[c], commandBuffer);

        [info.commandBuffers[i]->commandBuffer->commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
            if (buffer.error) {
                NSLog(@"Command buffer error: %s", buffer.error.localizedDescription.UTF8String);
            }
            if (atomic_fetch_sub_explicit(&buffersLeft, 1, memory_order_acq_rel) == 1) {
                fenceToSignal->signaled = GN_TRUE;
            }
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
