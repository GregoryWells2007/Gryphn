#include <core/sync_objects/gryphn_fence.h>
#include <core/devices/metal_output_devices.h>
#include <Metal/Metal.hpp>

struct gnPlatformFence {
    MTL::SharedEvent* fence;
    MTL::SharedEventListener* listener;
    dispatch_semaphore_t semaphore;
};

GN_EXPORT gnReturnCode gnCreateFenceFn(gnFence* fence, const gnOutputDevice& device) {
    fence->fence = new gnPlatformFence();
    fence->fence->fence = device.outputDevice->device->newSharedEvent();
    fence->fence->listener = MTL::SharedEventListener::alloc()->init();
    fence->fence->semaphore = dispatch_semaphore_create(1);
    return GN_SUCCESS;
}
GN_EXPORT void gnWaitForFenceFn(const gnFence& fence) {
    dispatch_semaphore_wait(fence.fence->semaphore, DISPATCH_TIME_FOREVER);
}
GN_EXPORT void gnResetFenceFn(gnFence& fence) {
    dispatch_semaphore_signal(fence.fence->semaphore);
    fence.fence->fence->setSignaledValue(0);
    fence.fence->fence->notifyListener(
        fence.fence->listener,
        1,
        ^(MTL::SharedEvent* ev, uint64_t val) {
            dispatch_semaphore_signal(fence.fence->semaphore);
        }
    );
}
GN_EXPORT void gnDestroyFenceFn(gnFence& fence) {
    fence.fence->fence->release();
}
