// #ifdef GN_EXT_GN_EXT_SYNCHRONIZATION

#include "gryphn_fence.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnCreateFence(gnFenceHandle* fence, gnDevice device) {
    *fence = malloc(sizeof(struct gnFence_t));
    (*fence)->device = device;
    (*fence)->signaled = GN_FALSE;
    return device->instance->callingLayer->syncFunctions._gnCreateFence(*fence, device);
}
void gnSignalFence(gnFenceHandle fence) {
    fence->signaled = GN_TRUE;
}
void gnWaitForFence(gnFenceHandle fence, uint64_t timeout) {
    if (fence->signaled == GN_TRUE) return;
    fence->device->instance->callingLayer->syncFunctions._gnWaitForFence(fence, timeout);
}
void gnResetFence(gnFenceHandle fence) {
    fence->signaled = GN_FALSE;
    fence->device->instance->callingLayer->syncFunctions._gnResetFence(fence);
}
void gnDestroyFence(gnFenceHandle fence) {
    fence->device->instance->callingLayer->syncFunctions._gnDestroyFence(fence);
}

// #endif
