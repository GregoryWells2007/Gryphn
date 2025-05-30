#include "gryphn_fence.h"
#include "core/gryphn_platform_functions.h"
#include "stdio.h"

gnReturnCode gnCreateFence(struct gnFence_t* fence, struct gnOutputDevice_t* device) {
    fence->device = device;
    fence->signaled = gnFalse;
    return device->deviceFunctions->_gnCreateFence(fence, device);
}
void gnSignalFence(struct gnFence_t* fence) {
    fence->signaled = gnTrue;
    // fence->device->deviceFunctions->_gnSignalFence(fence);
}
void gnWaitForFence(struct gnFence_t* fence, uint64_t timeout) {
    if (fence->signaled == gnTrue) return;
    fence->device->deviceFunctions->_gnWaitForFence(fence, timeout);
}
void gnResetFence(struct gnFence_t* fence) {
    fence->signaled = gnFalse;
    fence->device->deviceFunctions->_gnResetFence(fence);
}
void gnDestroyFence(struct gnFence_t* fence) {
    fence->device->deviceFunctions->_gnDestroyFence(fence);
}
