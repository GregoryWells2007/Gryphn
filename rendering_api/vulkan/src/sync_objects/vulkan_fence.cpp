#include "vulkan_fence.h"
#include "../output_device/vulkan_output_devices.h"

GN_EXPORT gnReturnCode gnCreateFenceFn(gnFence* fence, const gnOutputDevice& device) {
    if (fence->fence == nullptr) fence->fence = new gnPlatformFence();

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateFence(device.outputDevice->device, &fenceInfo, nullptr, &fence->fence->fence) != VK_SUCCESS) {
        return GN_FAILED;
    }

    fence->fence->device = const_cast<gnOutputDevice*>(&device);

    return GN_SUCCESS;
}
GN_EXPORT void gnWaitForFenceFn(const gnFence& fence) {
    vkWaitForFences(fence.fence->device->outputDevice->device, 1, &fence.fence->fence, VK_TRUE, UINT64_MAX);
}
GN_EXPORT void gnResetFenceFn(const gnFence& fence) {
    vkResetFences(fence.fence->device->outputDevice->device, 1, &fence.fence->fence);
}
GN_EXPORT void gnDestroyFenceFn(const gnFence& fence) {
    vkDestroyFence(fence.fence->device->outputDevice->device, fence.fence->fence, nullptr);
}
