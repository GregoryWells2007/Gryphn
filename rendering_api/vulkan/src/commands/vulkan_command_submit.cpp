#include <gryphn/gryphn_utils.h>
#include "core/commands/submit_command/gryphn_command_submit.h"
#include "../sync_objects/vulkan_sync_semaphore.h"
#include "vulkan_command_buffer.h"
#include "../sync_objects/vulkan_fence.h"

struct gnPlatformCommandSubmitData {
    VkSubmitInfo submitInfo{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO
    };
    VkResult result;
};

VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

void gnCommandSubmitDataSetWaitSemaphoreFn(gnCommandSubmitData& data, const gnSyncSemaphore& semaphore) {
    data.commandSubmitData->submitInfo.waitSemaphoreCount = 1;
    data.commandSubmitData->submitInfo.pWaitSemaphores = &semaphore.semaphore->semaphore;
    data.commandSubmitData->submitInfo.pWaitDstStageMask = waitStages;
}

void gnCommandSubmitDataSetCommandBufferFn(gnCommandSubmitData& data, const gnCommandBuffer& commandBuffer) {
    data.commandSubmitData->submitInfo.commandBufferCount = 1;
    data.commandSubmitData->submitInfo.pCommandBuffers = &commandBuffer.commandBuffer->commandBuffer;
}

void gnCommandSubmitDataSetSignalSemaphoreFn(gnCommandSubmitData& data, const gnSyncSemaphore& semaphore) {
    data.commandSubmitData->submitInfo.signalSemaphoreCount = 1;
    data.commandSubmitData->submitInfo.pSignalSemaphores = &semaphore.semaphore->semaphore;
}
GN_EXPORT gnPresentationQueueState gnCommandSubmitGetValidPresentationQueueFn(gnCommandSubmitData& data) {
    if (data.commandSubmitData->result == VK_ERROR_OUT_OF_DATE_KHR) {
        return GN_OUT_OF_DATE;
    } else if (data.commandSubmitData->result == VK_SUBOPTIMAL_KHR) {
        return GN_SUBOPTIMAL;
    }
    else if (data.commandSubmitData->result == VK_SUCCESS) {
        return GN_VALID;
    }
    return GN_VALID;
}
GN_EXPORT gnReturnCode gnCommandSubmitFn(gnCommandSubmitData& data, const gnFence& fence) {
    if (data.commandSubmitData == nullptr) data.commandSubmitData = new gnPlatformCommandSubmitData();

    gnCommandSubmitDataSetWaitSemaphoreFn(data, *data.waitSemaphore);
    gnCommandSubmitDataSetCommandBufferFn(data, *data.commandBuffer);
    gnCommandSubmitDataSetSignalSemaphoreFn(data, *data.signalSemaphore);

    data.commandSubmitData->result = vkQueueSubmit(fence.fence->device->outputDevice->graphicsQueue, 1, &data.commandSubmitData->submitInfo, fence.fence->fence);

    if (data.commandSubmitData->result != VK_SUCCESS) {
        return GN_FAILED;
    }

    return GN_SUCCESS;
}
