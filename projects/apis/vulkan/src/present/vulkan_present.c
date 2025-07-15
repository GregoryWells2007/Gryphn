#include "vulkan_present.h"
#include "extensions/synchronization/commands/gryphn_sync_present.h"
#include "vulkan_surface/vulkan_surface.h"

gnReturnCode vulkanPresentSync(gnDevice device, gnPresentSyncInfo info) {
    VkSemaphore* waitSemaphores = malloc(sizeof(VkSemaphore) * info.waitCount);
    for (int i = 0; i < info.waitCount; i++) waitSemaphores[i] = info.waitSemaphores[i]->semaphore->semaphore;

    VkSwapchainKHR* swapchains = malloc(sizeof(VkSwapchainKHR) * info.presentationQueueCount);
    for (int i = 0; i < info.presentationQueueCount; i++) swapchains[i] = info.presentationQueues[i]->presentationQueue->swapChain;

    VkPresentInfoKHR presentInfo = {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = info.waitCount,
        .pWaitSemaphores = waitSemaphores,
        .swapchainCount = info.presentationQueueCount,
        .pSwapchains = swapchains,
        .pImageIndices = info.imageIndices
    };

    VkResult result = vkQueuePresentKHR(device->outputDevice->queues[info.presentationQueues[0]->info.surface->windowSurface->presentQueueIndex].queue, &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR) return GN_OUT_OF_DATE_PRESENTATION_QUEUE;
    if (result == VK_SUBOPTIMAL_KHR) return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
    return GN_SUCCESS;
}


gnReturnCode vulkanPresent(gnDevice device, gnPresentInfo info) {
    VkSwapchainKHR* swapchains = malloc(sizeof(VkSwapchainKHR) * info.presentationQueueCount);
    for (int i = 0; i < info.presentationQueueCount; i++) swapchains[i] = info.presentationQueues[i]->presentationQueue->swapChain;

    VkPresentInfoKHR presentInfo = {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 0,
        .pWaitSemaphores = NULL,
        .swapchainCount = info.presentationQueueCount,
        .pSwapchains = swapchains,
        .pImageIndices = info.imageIndices
    };

    VkResult result = vkQueuePresentKHR(device->outputDevice->queues[info.presentationQueues[0]->info.surface->windowSurface->presentQueueIndex].queue, &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR) return GN_OUT_OF_DATE_PRESENTATION_QUEUE;
    if (result == VK_SUBOPTIMAL_KHR) return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
    return GN_SUCCESS;
}
