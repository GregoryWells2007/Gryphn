#include "vulkan_submit.h"

gnReturnCode vulkanSubmitSyncQueue(gnOutputDevice device, gnQueue queue, gnSubmitSyncInfo info) {
    VkSemaphore* waitSemaphores = malloc(sizeof(VkSemaphore) * info.waitCount);
    VkPipelineStageFlags* waitStages = malloc(sizeof(VkPipelineStageFlags) * info.waitCount);
    for (int i = 0; i < info.waitCount; i++) waitSemaphores[i] = info.waitSemaphores[i]->semaphore->semaphore;
    for (int i = 0; i < info.waitCount; i++) waitStages[i] = vkGryphnRenderPassStage(info.waitStages[i]);

    VkCommandBuffer* commandBuffers = malloc(sizeof(VkCommandBuffer) * info.commandBufferCount);
    for (int i = 0; i < info.commandBufferCount; i++) commandBuffers[i] = info.commandBuffers[i]->commandBuffer->buffer;

    VkSemaphore* signalSemaphores = malloc(sizeof(VkSemaphore) * info.signalCount);
    for (int i = 0; i < info.signalCount; i++) signalSemaphores[i] = info.signalSemaphores[i]->semaphore->semaphore;

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

    if (vkQueueSubmit((VkQueue)queue, 1, &submitInfo, info.fence->fence->fence) != VK_SUCCESS) {
        free(waitSemaphores);
        free(waitStages);
        free(commandBuffers);
        free(signalSemaphores);
        return GN_FAILED_TO_SUBMIT_COMMAND_BUFFER;
    }
    free(waitSemaphores);
    free(waitStages);
    free(commandBuffers);
    free(signalSemaphores);
    return GN_SUCCESS;
}

gnReturnCode vulkanSubmitSync(gnDevice device, gnSubmitSyncInfo info) {
    return vulkanSubmitSyncQueue(device, (gnQueue)device->outputDevice->queues[device->outputDevice->graphicsQueueIndex].queue, info);
}

gnReturnCode vulkanSubmitQueue(gnOutputDevice device, gnQueue queue, gnSubmitInfo info) {
    VkCommandBuffer* commandBuffers = malloc(sizeof(VkCommandBuffer) * info.commandBufferCount);
    for (int i = 0; i < info.commandBufferCount; i++) commandBuffers[i] = info.commandBuffers[i]->commandBuffer->buffer;

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
    if (vkQueueSubmit((VkQueue)queue, 1, &submitInfo, device->outputDevice->barrierFence) != VK_SUCCESS)
        return GN_FAILED_TO_SUBMIT_COMMAND_BUFFER;
    vkWaitForFences(device->outputDevice->device, 1, &device->outputDevice->barrierFence, VK_TRUE, UINT64_MAX);
    return GN_SUCCESS;
}

gnReturnCode vulkanSubmit(gnDevice device, gnSubmitInfo info) {
    return vulkanSubmitQueue(device, (gnQueue)device->outputDevice->queues[device->outputDevice->graphicsQueueIndex].queue, info);
}
