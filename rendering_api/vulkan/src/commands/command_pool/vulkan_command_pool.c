#include "vulkan_command_pool.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode gnCreateCommandPoolFn(struct gnCommandPool_t* commandPool, struct gnOutputDevice_t* device, struct gnCommandPoolInfo_t info) {
    commandPool->commandPool = malloc(sizeof(gnPlatformCommandPool));

    VkCommandPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = info.queueIndex
    };

    if (vkCreateCommandPool(device->outputDevice->device, &poolInfo, NULL, &commandPool->commandPool->commandPool) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_COMMAND_POOL;
    }

    return GN_SUCCESS;
}

void gnDestroyCommandPoolFn(struct gnCommandPool_t* commandPool) {
    vkDestroyCommandPool(commandPool->device->outputDevice->device, commandPool->commandPool->commandPool, NULL);
    free(commandPool->commandPool);
}
