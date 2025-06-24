#include "vulkan_present.h"

gnReturnCode present(gnDevice device, gnPresentInfo info) {
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

    VkQueue queue;
    vkGetDeviceQueue(device->outputDevice->device, info.queueIndex, 0, &queue);

    VkResult result = vkQueuePresentKHR(queue, &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR) return GN_OUT_OF_DATE_PRESENTATION_QUEUE;
    if (result == VK_SUBOPTIMAL_KHR) return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
    return GN_SUCCESS;
}
