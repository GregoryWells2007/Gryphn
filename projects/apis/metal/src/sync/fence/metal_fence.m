#include "metal_fence.h"
#include "devices/metal_output_devices.h"

gnReturnCode createMetalFence(gnFence fence, gnDevice device) {
    fence->fence = malloc(sizeof(gnPlatformFence));
    fence->fence->event = [device->outputDevice->device newSharedEvent];
    fence->fence->currentValue = 0;
    return GN_SUCCESS;
}
void waitForMetalFence(gnFence fence, uint64_t timeout) {
    [fence->fence->event waitUntilSignaledValue:fence->fence->currentValue timeoutMS:timeout];
}
void resetMetalFence(gnFence fence) {
    fence->fence->currentValue++;
}
void destroyMetalFence(gnFence fence) {
    [fence->fence->event release];
    free(fence->fence);
}
