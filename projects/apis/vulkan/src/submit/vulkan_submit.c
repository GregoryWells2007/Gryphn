#include "vulkan_submit.h"
#include "vulkan_result_converter.h"

gnReturnCode vulkanSubmitSyncQueue(gnOutputDevice device, gnQueue queue, gnSubmitSyncInfo info) {
    if (device == GN_NULL_HANDLE) return GN_INVALID_HANDLE;

    VkSemaphore* waitSemaphores = malloc(sizeof(VkSemaphore) * info.waitCount);
    VkPipelineStageFlags* waitStages = malloc(sizeof(VkPipelineStageFlags) * info.waitCount);
    for (uint32_t i = 0; i < info.waitCount; i++) waitSemaphores[i] = info.waitSemaphores[i]->semaphore->semaphore;
    for (uint32_t i = 0; i < info.waitCount; i++) waitStages[i] = vkGryphnRenderPassStage(info.waitStages[i]);

    VkCommandBuffer* commandBuffers = malloc(sizeof(VkCommandBuffer) * info.commandBufferCount);
    for (uint32_t i = 0; i < info.commandBufferCount; i++) commandBuffers[i] = info.commandBuffers[i]->commandBuffer->buffer;

    VkSemaphore* signalSemaphores = malloc(sizeof(VkSemaphore) * info.signalCount);
    for (uint32_t i = 0; i < info.signalCount; i++) signalSemaphores[i] = info.signalSemaphores[i]->semaphore->semaphore;

    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = info.waitCount,
        .pWaitSemaphores = waitSemaphores,
        .pWaitDstStageMask = waitStages,
        .commandBufferCount = info.commandBufferCount,
        .pCommandBuffers = commandBuffers,
        .signalSemaphoreCount = info.signalCount,
        .pSignalSemaphores = signalSemaphores
    };

    return VkResultToGnReturnCode(vkQueueSubmit((VkQueue)queue, 1, &submitInfo, info.fence->fence->fence));
}

gnReturnCode vulkanSubmitSync(gnDevice device, gnSubmitSyncInfo info) {
    return vulkanSubmitSyncQueue(device, (gnQueue)device->outputDevice->queues[device->outputDevice->graphicsQueueIndex].queue, info);
}

gnReturnCode vulkanSubmitQueue(gnOutputDevice device, gnQueue queue, gnSubmitInfo info) {
    VkCommandBuffer* commandBuffers = malloc(sizeof(VkCommandBuffer) * info.commandBufferCount);
    for (uint32_t i = 0; i < info.commandBufferCount; i++) commandBuffers[i] = info.commandBuffers[i]->commandBuffer->buffer;

    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 0,
        .pWaitSemaphores = NULL,
        .pWaitDstStageMask = NULL,
        .commandBufferCount = info.commandBufferCount,
        .pCommandBuffers = commandBuffers,
        .signalSemaphoreCount = 0,
        .pSignalSemaphores = NULL
    };

    vkResetFences(device->outputDevice->device, 1, &device->outputDevice->barrierFence);
    VkResult res = vkQueueSubmit((VkQueue)queue, 1, &submitInfo, device->outputDevice->barrierFence);
    if (res != VK_SUCCESS)
        return VkResultToGnReturnCode(res);
    vkWaitForFences(device->outputDevice->device, 1, &device->outputDevice->barrierFence, VK_TRUE, UINT64_MAX);
    return VkResultToGnReturnCode(res);
}

gnReturnCode vulkanSubmit(gnDevice device, gnSubmitInfo info) {
    return vulkanSubmitQueue(device, (gnQueue)device->outputDevice->queues[device->outputDevice->graphicsQueueIndex].queue, info);
}
