#include "vulkan_fence.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode createFence(gnFence fence, gnDevice device) {
    fence->fence = malloc(sizeof(gnPlatformFence));
    VkFenceCreateInfo fenceInfo = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO
    };

    if (vkCreateFence(device->outputDevice->device, &fenceInfo, NULL, &fence->fence->fence) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_FENCE;
    return GN_SUCCESS;
}
void waitForFence(gnFence fence, uint64_t timeout) {
    vkWaitForFences(fence->device->outputDevice->device, 1, &fence->fence->fence, VK_TRUE, timeout);
}
void resetFence(gnFence fence) {
    vkResetFences(fence->device->outputDevice->device, 1, &fence->fence->fence);
}
void destroyFence(gnFence fence) {
    vkDestroyFence(fence->device->outputDevice->device, fence->fence->fence, NULL);
    free(fence->fence);
}
