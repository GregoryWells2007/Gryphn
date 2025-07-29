#include <vulkan/vulkan.h>
#include <output_device/vulkan_physical_device.h>
#include <output_device/vulkan_output_devices.h>
#include "vulkan_device_extensions.h"
#include "instance/gryphn_instance.h"
#include "commands/command_buffer/vulkan_command_buffer.h"
#include "vulkan_result_converter.h"

gnReturnCode createOutputDevice(gnOutputDeviceHandle outputDevice, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo) {
    outputDevice->outputDevice = malloc(sizeof(gnPlatformOutputDevice));

    int createQueueCount = 0;
    VkDeviceQueueCreateInfo* queueCreateInfos = NULL;

    if (!instance->enabledExtensions[GN_EXT_QUEUES]) {
        queueCreateInfos = malloc(sizeof(VkDeviceQueueCreateInfo) * deviceInfo.physicalDevice->physicalDevice->neededQueueCount);
        createQueueCount = deviceInfo.physicalDevice->physicalDevice->neededQueueCount;
        float queuePriority = 1.0f;
        for (int i = 0; i < deviceInfo.physicalDevice->physicalDevice->neededQueueCount; i++) {
            queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfos[i].flags = 0;
            queueCreateInfos[i].queueCount = 1;
            queueCreateInfos[i].queueFamilyIndex = deviceInfo.physicalDevice->physicalDevice->neededQueues[i].queueIndex;
            queueCreateInfos[i].pQueuePriorities = &queuePriority;
        }
    } else {
        createQueueCount = deviceInfo.queueInfoCount;
        queueCreateInfos = malloc(sizeof(VkDeviceQueueCreateInfo) * deviceInfo.queueInfoCount);
        for (int i = 0; i < deviceInfo.queueInfoCount; i++) {
            queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfos[i].flags = 0;
            queueCreateInfos[i].queueCount = deviceInfo.queueInfos[i].queueCount;
            queueCreateInfos[i].queueFamilyIndex = deviceInfo.queueInfos[i].queueFamilyIndex;
            queueCreateInfos[i].pQueuePriorities = deviceInfo.queueInfos[i].queuePrioritys;
        }
    }

    VkPhysicalDeviceFeatures deviceFeatures = {
        .samplerAnisotropy = VK_TRUE
    };

    VkDeviceCreateInfo deviceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = createQueueCount,
        .pQueueCreateInfos = queueCreateInfos,
        .pEnabledFeatures = &deviceFeatures
    };
    deviceCreateInfo.ppEnabledExtensionNames = vkGetGryphnDeviceExtensions(&deviceCreateInfo.enabledExtensionCount, deviceInfo.physicalDevice->physicalDevice->device);

    outputDevice->outputDevice->enabledOversizedDescriptorPools = GN_FALSE;
    for (int i = 0; i < deviceCreateInfo.enabledExtensionCount; i++)
        if (strcmp(deviceCreateInfo.ppEnabledExtensionNames[i], VK_NV_DESCRIPTOR_POOL_OVERALLOCATION_EXTENSION_NAME) == 0) outputDevice->outputDevice->enabledOversizedDescriptorPools = GN_TRUE;

    if (instance->hasDebugger)
        deviceCreateInfo.enabledLayerCount = 0;
    else {
        const char* validation_layers[1] = { "VK_LAYER_KHRONOS_validation" };
        deviceCreateInfo.enabledLayerCount = 1;
        deviceCreateInfo.ppEnabledLayerNames = validation_layers;
    }

    VkResult result = vkCreateDevice(deviceInfo.physicalDevice->physicalDevice->device, &deviceCreateInfo, NULL, &outputDevice->outputDevice->device);
    if (result != VK_SUCCESS)
        return VkResultToGnReturnCode(result);

    outputDevice->outputDevice->queues = malloc(sizeof(vulkanQueue) * deviceInfo.physicalDevice->physicalDevice->neededQueueCount);
    uint32_t transferQueue = 0;
    for (int i = 0; i < deviceInfo.physicalDevice->physicalDevice->neededQueueCount; i++) {
        outputDevice->outputDevice->queues[i].queueInfo = deviceInfo.physicalDevice->physicalDevice->neededQueues[i];

        vkGetDeviceQueue(outputDevice->outputDevice->device, deviceInfo.physicalDevice->physicalDevice->neededQueues[i].queueIndex, 0, &outputDevice->outputDevice->queues[i].queue);
        if ((outputDevice->outputDevice->queues[i].queueInfo.createFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT) {
            outputDevice->outputDevice->transferQueueIndex = i;
            transferQueue = outputDevice->outputDevice->queues[i].queueInfo.queueIndex;
        }

        if ((outputDevice->outputDevice->queues[i].queueInfo.createFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT) {
            outputDevice->outputDevice->graphicsQueueIndex = i;
        }
    }

    VkCommandPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = transferQueue
    };

    VkResult command_pool_result = vkCreateCommandPool(outputDevice->outputDevice->device, &poolInfo, NULL, &outputDevice->outputDevice->transferCommandPool);
    if (command_pool_result != VK_SUCCESS)
        return VkResultToGnReturnCode(command_pool_result);

    VkFenceCreateInfo fenceInfo = { .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
    VkResult fence_result = vkCreateFence(outputDevice->outputDevice->device, &fenceInfo, NULL, &outputDevice->outputDevice->barrierFence);
    if (fence_result != VK_SUCCESS) VkResultToGnReturnCode(fence_result);

    // create the massive staging buffer
    outputDevice->outputDevice->stagingBufferSize = 128 * 1024 * 1024;
    gnReturnCode code = VkCreateBuffer(
        &outputDevice->outputDevice->stagingBuffer,
        outputDevice->outputDevice->stagingBufferSize, outputDevice,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT
    );
    return code; // lowkey is a hack
}

void waitForDevice(const gnOutputDeviceHandle device) {
    vkDeviceWaitIdle(device->outputDevice->device);
}

void destroyOutputDevice(gnOutputDeviceHandle device) {
    vkDestroyFence(device->outputDevice->device, device->outputDevice->barrierFence, NULL);
    gnDestroyVulkanBuffer(&device->outputDevice->stagingBuffer, device->outputDevice->device);
    vkDestroyCommandPool(device->outputDevice->device, device->outputDevice->transferCommandPool, NULL);
    vkDestroyDevice(device->outputDevice->device, NULL);
    free(device->outputDevice);
}


VkCommandBuffer gnBeginVulkanTransferOperation(gnDevice device) {
    return VkBeginTransferOperation(device->outputDevice->device, device->outputDevice->transferCommandPool);
}
void gnEndVulkanTransferOperation(gnDevice device, VkCommandBuffer buffer) {
    VkEndTransferOperation(buffer, device->outputDevice->transferCommandPool, device->outputDevice->queues[device->outputDevice->transferQueueIndex].queue, device->outputDevice->device);
}
