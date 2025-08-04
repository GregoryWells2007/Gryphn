#include "metal_submit.h"
#include "instance/gryphn_debugger.h"
#include "synchronization/fence/gryphn_fence.h"
#include "sync/fence/metal_fence.h"
#include "instance/gryphn_instance.h"

gnReturnCode metalSyncSubmit(gnOutputDevice device, gnSubmitSyncInfo info) {
    if (device == GN_NULL_HANDLE) return GN_INVALID_HANDLE;

    __block gnFence fenceToSignal = info.fence;
    __block atomic_int buffersLeft;
    atomic_init(&buffersLeft, info.commandBufferCount);

    for (uint32_t i = 0; i < info.commandBufferCount; i++) {
        id <MTLCommandBuffer> buffer = [info.commandBuffers[i]->commandPool->commandPool->commandQueue commandBuffer];
        for (uint32_t c = 0; c < info.waitCount; c++)
            mtlWaitSemaphore(info.waitSemaphores[c], buffer);
        [buffer commit];

        id<MTLCommandBuffer> commandBuffer = info.commandBuffers[i]->commandBuffer->commandBuffer;

        for (uint32_t c = 0; c < info.signalCount; c++)
            mtlSignalSemaphore(info.signalSemaphores[c], commandBuffer);

        [info.commandBuffers[i]->commandBuffer->commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
            if (buffer.error)
                gnDebuggerSetErrorMessage(info.commandBuffers[i]->instance->debugger, (gnMessageData){
                    .message = gnCombineStrings(gnCreateString("Command buffer failed to run "), buffer.error.localizedDescription.UTF8String)
                });
            if (atomic_fetch_sub_explicit(&buffersLeft, 1, memory_order_acq_rel) == 1)
                signalMetalFence(fenceToSignal);
        }];

        [commandBuffer commit];
    }

    return GN_SUCCESS;
}

gnReturnCode metalSubmit(gnOutputDevice device, gnSubmitInfo info) {
    if (device == GN_NULL_HANDLE) return GN_INVALID_HANDLE;

    for (uint32_t i = 0; i < info.commandBufferCount; i++) {
        id<MTLCommandBuffer> commandBuffer = info.commandBuffers[i]->commandBuffer->commandBuffer;
        [commandBuffer commit];
    }

    [info.commandBuffers[info.commandBufferCount - 1]->commandBuffer->commandBuffer waitUntilCompleted];
    return GN_SUCCESS;
}
