#include "vulkan_submit.h"

gnReturnCode vulkanSubmitSync(gnDevice device, gnSubmitSyncInfo info) {
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

    VkQueue queue;
    vkGetDeviceQueue(device->outputDevice->device, info.queueIndex, 0, &queue);

    if (vkQueueSubmit(queue, 1, &submitInfo, info.fence->fence->fence) != VK_SUCCESS) {
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

gnReturnCode vulkanSubmit(gnDevice device, gnSubmitInfo info) {
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

    VkQueue queue;
    vkGetDeviceQueue(device->outputDevice->device, info.queueIndex, 0, &queue);

    if (vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
        return GN_FAILED_TO_SUBMIT_COMMAND_BUFFER;
    return GN_SUCCESS;
}
