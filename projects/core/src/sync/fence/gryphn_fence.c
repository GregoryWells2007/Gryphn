#include "gryphn_fence.h"
#include "output_device/gryphn_output_device.h"

gnReturnCode gnCreateFence(gnFenceHandle* fence, struct gnOutputDevice_t* device) {
    *fence = malloc(sizeof(struct gnFence_t));
    (*fence)->device = device;
    (*fence)->signaled = gnFalse;
    return device->deviceFunctions->_gnCreateFence(*fence, device);
}
void gnSignalFence(gnFenceHandle fence) {
    fence->signaled = gnTrue;
}
void gnWaitForFence(gnFenceHandle fence, uint64_t timeout) {
    if (fence->signaled == gnTrue) return;
    fence->device->deviceFunctions->_gnWaitForFence(fence, timeout);
}
void gnResetFence(gnFenceHandle fence) {
    fence->signaled = gnFalse;
    fence->device->deviceFunctions->_gnResetFence(fence);
}
void gnDestroyFence(gnFenceHandle fence) {
    fence->device->deviceFunctions->_gnDestroyFence(fence);
}
