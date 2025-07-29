#include "vulkan_fence.h"
#include "output_device/vulkan_output_devices.h"
#include <vulkan_result_converter.h>

gnReturnCode createFence(gnFence fence, gnDevice device) {
    fence->fence = malloc(sizeof(gnPlatformFence));
    VkFenceCreateInfo fenceInfo = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO
    };
    return VkResultToGnReturnCode(vkCreateFence(device->outputDevice->device, &fenceInfo, NULL, &fence->fence->fence));
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
