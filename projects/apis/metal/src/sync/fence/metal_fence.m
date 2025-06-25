#include "metal_fence.h"
#include "devices/metal_output_devices.h"

gnReturnCode gnCreateFenceFn(struct gnFence_t* fence, struct gnOutputDevice_t* device) {
    // fence->fence = malloc(sizeof(gnPlatformFence));

    // fence->fence->fence = [device->outputDevice->device newSharedEvent];
    // fence->fence->listener = [[MTLSharedEventListener alloc] init];
    // fence->fence->semaphore = dispatch_semaphore_create(1);

    return GN_SUCCESS;
}
void gnSignalFenceFn(struct gnFence_t* fence) {
    // dispatch_semaphore_signal(fence->fence->semaphore);
}
void gnWaitForFenceFn(struct gnFence_t* fence, uint64_t timeout) {
    // dispatch_semaphore_wait(fence->fence->semaphore, timeout);
    while (fence->signaled == gnFalse) {}
}
void gnResetFenceFn(struct gnFence_t* fence) {
    // dispatch_semaphore_signal(fence->fence->semaphore);
    // [fence->fence->fence setSignaledValue:0];
    // [fence->fence->fence notifyListener:fence->fence->listener
    //     atValue:1
    //     block:^(id<MTLSharedEvent> ev, uint64_t val) {
    //     dispatch_semaphore_signal(fence->fence->semaphore);
    // }];
}
void gnDestroyFenceFn(struct gnFence_t* fence) {
    // [fence->fence->fence release];
    // [fence->fence->listener release];
    // free(fence->fence);
}
