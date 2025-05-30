#include "vulkan_fence.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode gnCreateFenceFn(struct gnFence_t* fence, struct gnOutputDevice_t* device) {
    fence->fence = malloc(sizeof(gnPlatformFence));
    VkFenceCreateInfo fenceInfo = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO
    };
    if (vkCreateFence(device->outputDevice->device, &fenceInfo, NULL, &fence->fence->fence) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_FENCE;
    return GN_SUCCESS;
}
void gnSignalFenceFn(struct gnFence_t* fence) {}
void gnWaitForFenceFn(struct gnFence_t* fence, uint64_t timeout) {
    vkWaitForFences(fence->device->outputDevice->device, 1, &fence->fence->fence, VK_TRUE, timeout);
}
void gnResetFenceFn(struct gnFence_t* fence) {
    vkResetFences(fence->device->outputDevice->device, 1, &fence->fence->fence);
}
void gnDestroyFenceFn(struct gnFence_t* fence) {
    vkDestroyFence(fence->device->outputDevice->device, fence->fence->fence, NULL);
    free(fence->fence);
}
