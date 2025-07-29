#include "metal_fence.h"
#include "devices/metal_output_devices.h"

gnReturnCode createMetalFence(gnFence fence, struct gnOutputDevice_t* device) {
    // fence->fence = malloc(sizeof(gnPlatformFence));

    // fence->fence->fence = [device->outputDevice->device newSharedEvent];
    // fence->fence->listener = [[MTLSharedEventListener alloc] init];
    // fence->fence->semaphore = dispatch_semaphore_create(1);

    return GN_SUCCESS;
}
void singalMetalFence(gnFence fence) {
    // dispatch_semaphore_signal(fence->fence->semaphore);
}
void waitForMetalFence(gnFence fence, uint64_t timeout) {
    // dispatch_semaphore_wait(fence->fence->semaphore, timeout);
    while (fence->signaled == GN_FALSE) {}
}
void resetMetalFence(gnFence fence) {
    // dispatch_semaphore_signal(fence->fence->semaphore);
    // [fence->fence->fence setSignaledValue:0];
    // [fence->fence->fence notifyListener:fence->fence->listener
    //     atValue:1
    //     block:^(id<MTLSharedEvent> ev, uint64_t val) {
    //     dispatch_semaphore_signal(fence->fence->semaphore);
    // }];
}
void destroyMetalFence(gnFence fence) {
    // [fence->fence->fence release];
    // [fence->fence->listener release];
    // free(fence->fence);
}
