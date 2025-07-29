#include "vulkan_semaphore.h"
#include "output_device/vulkan_output_devices.h"
#include <vulkan_result_converter.h>

gnReturnCode createSemaphore(gnSemaphore semaphore, gnDevice device) {
    semaphore->semaphore = malloc(sizeof(gnPlatformSemaphore));
    VkSemaphoreCreateInfo semaphoreInfo = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
    };
    return VkResultToGnReturnCode(vkCreateSemaphore(device->outputDevice->device, &semaphoreInfo, NULL, &semaphore->semaphore->semaphore));
}
void destroySemaphore(gnSemaphore semaphore) {
    vkDestroySemaphore(semaphore->device->outputDevice->device, semaphore->semaphore->semaphore, NULL);
    free(semaphore->semaphore);
}
