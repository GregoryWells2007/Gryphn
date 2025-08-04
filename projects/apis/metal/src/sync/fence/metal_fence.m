#include "metal_fence.h"
#include "devices/metal_output_devices.h"

gnReturnCode createMetalFence(gnFence fence, gnDevice device) {
    if (device == GN_NULL_HANDLE) return GN_INVALID_HANDLE;

    fence->fence = malloc(sizeof(gnPlatformFence));
    fence->fence->event = [[device->outputDevice->device newSharedEvent] retain];
    return GN_SUCCESS;
}
void waitForMetalFence(gnFence fence, uint64_t timeout) {
    [fence->fence->event waitUntilSignaledValue:1 timeoutMS:timeout];
}
void signalMetalFence(gnFence fence) {
    [fence->fence->event setSignaledValue:1];
}
void resetMetalFence(gnFence fence) {
    [fence->fence->event setSignaledValue:0];
}
void destroyMetalFence(gnFence fence) {
    [fence->fence->event release];
    free(fence->fence);
}
