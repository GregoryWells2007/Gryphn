#include "vulkan_present.h"
#include "extensions/synchronization/commands/gryphn_sync_present.h"
#include "vulkan_surface/vulkan_surface.h"
#include "vulkan_result_converter.h"

gnReturnCode vulkanQueuePresentSync(gnDevice device, gnQueue queue, gnPresentSyncInfo info) {
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

    return VkResultToGnReturnCode(vkQueuePresentKHR((VkQueue)queue, &presentInfo));
}

gnReturnCode vulkanPresentSync(gnDevice device, gnPresentSyncInfo info) {
    return vulkanQueuePresentSync(device, (gnQueue)device->outputDevice->queues[info.presentationQueues[0]->info.surface->windowSurface->presentQueueIndex].queue, info);
}

gnReturnCode vulkanQueuePresent(gnDevice device, gnQueue queue, gnPresentInfo info) {
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

    return VkResultToGnReturnCode(vkQueuePresentKHR((VkQueue)queue, &presentInfo));
}

gnReturnCode vulkanPresent(gnDevice device, gnPresentInfo info) {
    return vulkanQueuePresent(device, (gnQueue)device->outputDevice->queues[info.presentationQueues[0]->info.surface->windowSurface->presentQueueIndex].queue, info);
}
