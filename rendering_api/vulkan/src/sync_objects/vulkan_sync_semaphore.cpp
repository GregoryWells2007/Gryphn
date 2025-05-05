#include "vulkan_sync_semaphore.h"

GN_EXPORT gnReturnCode gnCreateSyncSemaphoreFn(gnSyncSemaphore* semaphore, const gnOutputDevice& device) {
    if (semaphore->semaphore == nullptr) semaphore->semaphore = new gnPlatformSyncSemaphore();

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    if (vkCreateSemaphore(device.outputDevice->device, &semaphoreInfo, nullptr, &semaphore->semaphore->semaphore) != VK_SUCCESS) {
        return GN_FAILED;
    }

    semaphore->semaphore->device = const_cast<gnOutputDevice*>(&device);

    return GN_SUCCESS;
}

GN_EXPORT void gnDestroySyncSemaphoreFn(const gnSyncSemaphore& semaphore) {
    vkDestroySemaphore(semaphore.semaphore->device->outputDevice->device, semaphore.semaphore->semaphore, nullptr);
}
