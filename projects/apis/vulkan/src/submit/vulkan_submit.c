#include <vulkan/vulkan.h>
#include "core/submit/gryphn_submit.h"
#include "sync/semaphore/vulkan_semaphore.h"
#include "sync/fence/vulkan_fence.h"
#include "commands/command_buffer/vulkan_command_buffer.h"
#include "output_device/vulkan_output_devices.h"
#include "renderpass/vulkan_render_pass_descriptor.h"


gnReturnCode gnSubmitFn(struct gnOutputDevice_t* device, struct gnSubmitInfo_t info) {
    VK_SUBPASS_EXTERNAL;

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
