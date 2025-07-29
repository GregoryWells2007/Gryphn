#include "vulkan_command_pool.h"
#include "output_device/vulkan_output_devices.h"
#include "instance/gryphn_instance.h"
#include "vulkan_result_converter.h"

gnReturnCode createCommandPool(gnCommandPool commandPool, gnDevice device, gnCommandPoolInfo info) {
    commandPool->commandPool = malloc(sizeof(gnPlatformCommandPool));

    VkCommandPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = info.queueFamilyIndex,
    };
    if (!device->instance->enabledExtensions[GN_EXT_QUEUES]) poolInfo.queueFamilyIndex = device->outputDevice->queues[device->outputDevice->graphicsQueueIndex].queueInfo.queueIndex;
    return VkResultToGnReturnCode(vkCreateCommandPool(device->outputDevice->device, &poolInfo, NULL, &commandPool->commandPool->commandPool));
}

void destroyCommandPool(gnCommandPool commandPool) {
    vkDestroyCommandPool(commandPool->device->outputDevice->device, commandPool->commandPool->commandPool, NULL);
    free(commandPool->commandPool);
}
