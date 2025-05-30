#include "vulkan_semaphore.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode gnCreateSemaphoreFn(struct gnSemaphore_t* semaphore, struct gnOutputDevice_t* device) {
    semaphore->semaphore = malloc(sizeof(gnPlatformSemaphore));
    VkSemaphoreCreateInfo semaphoreInfo = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
    };

    if (vkCreateSemaphore(device->outputDevice->device, &semaphoreInfo, NULL, &semaphore->semaphore->semaphore))
        return GN_FAILED_TO_CREATE_SEMAPHORE;
    return GN_SUCCESS;
}
void gnDestroySemaphoreFn(struct gnSemaphore_t* semaphore) {
    vkDestroySemaphore(semaphore->device->outputDevice->device, semaphore->semaphore->semaphore, NULL);
    free(semaphore->semaphore);
}
