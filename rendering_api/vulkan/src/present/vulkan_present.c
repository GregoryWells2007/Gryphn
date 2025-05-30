#include "core/present/gryphn_present.h"
#include "sync/semaphore/vulkan_semaphore.h"
#include "presentation_queue/vulkan_presentation_queue.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode gnPresentFn(struct gnOutputDevice_t* device, struct gnPresentInfo_t info) {
    VkSemaphore* waitSemaphores = malloc(sizeof(VkSemaphore) * info.waitCount);
    for (int i = 0; i < info.waitCount; i++) waitSemaphores[i] = info.waitSemaphores[i].semaphore->semaphore;

    VkSwapchainKHR* swapchains = malloc(sizeof(VkSwapchainKHR) * info.presentationQueueCount);
    for (int i = 0; i < info.presentationQueueCount; i++) swapchains[i] = info.presentationQueues[i].presentationQueue->swapChain;

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

    vkQueuePresentKHR(queue, &presentInfo);

    return GN_SUCCESS;
}
