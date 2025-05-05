#include "core/commands/present_command/gryphn_command_present.h"
#include "../presentation_queue/vulkan_presentation_queue.h"
#include "../sync_objects/vulkan_sync_semaphore.h"
#include "../output_device/vulkan_output_devices.h"

struct gnPlatformCommandPresentData {
    VkPresentInfoKHR presentInfo{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR
    };
    gnPresentationQueue* presentationQueue;
    VkResult result;
};

void gnCommandPresentDataSetSignalSemaphoreFn(gnCommandPresentData& presentCommandData, const gnSyncSemaphore& semaphore) {
    presentCommandData.commandPresentData->presentInfo.waitSemaphoreCount = 1;
    presentCommandData.commandPresentData->presentInfo.pWaitSemaphores = &semaphore.semaphore->semaphore;
}
void gnCommandPresentDataSetPresentationQueueFn(gnCommandPresentData& presentCommandData, const gnPresentationQueue& presentationQueue) {
    presentCommandData.commandPresentData->presentInfo.swapchainCount = 1;
    presentCommandData.commandPresentData->presentInfo.pSwapchains = &presentationQueue.presentationQueue->swapChain;

    presentCommandData.commandPresentData->presentationQueue = const_cast<gnPresentationQueue*>(&presentationQueue);
}

void gnCommandPresentDataSetImageIndexFn(gnCommandPresentData& presentCommandData, gnUInt* imageIndex) {
    presentCommandData.commandPresentData->presentInfo.pImageIndices = imageIndex;
}
GN_EXPORT gnPresentationQueueState gnCommandPresentGetValidPresentationQueueFn(gnCommandPresentData& presentCommandData) {
    if (presentCommandData.commandPresentData->result == VK_ERROR_OUT_OF_DATE_KHR) {
        return GN_OUT_OF_DATE;
    } else if (presentCommandData.commandPresentData->result == VK_SUBOPTIMAL_KHR) {
        return GN_SUBOPTIMAL;
    }
    else if (presentCommandData.commandPresentData->result == VK_SUCCESS) {
        return GN_VALID;
    }
    return GN_VALID;
}
GN_EXPORT gnReturnCode gnCommandPresentFn(gnCommandPresentData& presentCommandData) {
    if (presentCommandData.commandPresentData == nullptr) presentCommandData.commandPresentData = new gnPlatformCommandPresentData();

    gnCommandPresentDataSetSignalSemaphoreFn(presentCommandData, *presentCommandData.semaphore);
    gnCommandPresentDataSetPresentationQueueFn(presentCommandData, *presentCommandData.presentationQueue);
    gnCommandPresentDataSetImageIndexFn(presentCommandData, presentCommandData.imageIndex);

    uint32_t imageIndex = *presentCommandData.imageIndex;
    presentCommandData.commandPresentData->presentInfo.pImageIndices = &imageIndex;

    presentCommandData.commandPresentData->result =
        vkQueuePresentKHR(presentCommandData.commandPresentData->presentationQueue->presentationQueue->outputDevice->outputDevice->presentQueue, &presentCommandData.commandPresentData->presentInfo);
    if (presentCommandData.commandPresentData->result != VK_SUCCESS) {
        return GN_FAILED;
    }
    return GN_SUCCESS;
}
