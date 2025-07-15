#include <vulkan/vulkan.h>
#include <output_device/vulkan_physical_device.h>
#include <output_device/vulkan_output_devices.h>
#include "vulkan_device_extensions.h"
#include "instance/gryphn_instance.h"
#include "commands/command_buffer/vulkan_command_buffer.h"

gnReturnCode createOutputDevice(gnOutputDeviceHandle outputDevice, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo) {
    outputDevice->outputDevice = malloc(sizeof(gnPlatformOutputDevice));

    VkDeviceQueueCreateInfo* queueCreateInfos = malloc(sizeof(VkDeviceQueueCreateInfo) * deviceInfo.physicalDevice->physicalDevice->neededQueueCount);
    float queuePriority = 1.0f;
    for (int i = 0; i < deviceInfo.physicalDevice->physicalDevice->neededQueueCount; i++) {
        queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfos[i].flags = 0;
        queueCreateInfos[i].queueFamilyIndex = deviceInfo.physicalDevice->physicalDevice->neededQueues[i].queueIndex;
        queueCreateInfos[i].queueCount = 1;
        queueCreateInfos[i].pQueuePriorities = &queuePriority;
    }

    VkPhysicalDeviceFeatures deviceFeatures = {
        .samplerAnisotropy = VK_TRUE
    };

    VkDeviceCreateInfo deviceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = deviceInfo.physicalDevice->physicalDevice->neededQueueCount,
        .pQueueCreateInfos = queueCreateInfos,
        .pEnabledFeatures = &deviceFeatures
    };
    deviceCreateInfo.ppEnabledExtensionNames = vkGetGryphnDeviceExtensions(&deviceCreateInfo.enabledExtensionCount, deviceInfo.physicalDevice->physicalDevice->device);

    outputDevice->outputDevice->enabledOversizedDescriptorPools = gnFalse;
    for (int i = 0; i < deviceCreateInfo.enabledExtensionCount; i++)
        if (strcmp(deviceCreateInfo.ppEnabledExtensionNames[i], VK_NV_DESCRIPTOR_POOL_OVERALLOCATION_EXTENSION_NAME) == 0) outputDevice->outputDevice->enabledOversizedDescriptorPools = gnTrue;

    if (instance->hasDebugger)
        deviceCreateInfo.enabledLayerCount = 0;
    else {
        const char* validation_layers[1] = { "VK_LAYER_KHRONOS_validation" };
        deviceCreateInfo.enabledLayerCount = 1;
        deviceCreateInfo.ppEnabledLayerNames = validation_layers;
    }

    if (vkCreateDevice(deviceInfo.physicalDevice->physicalDevice->device, &deviceCreateInfo, NULL, &outputDevice->outputDevice->device) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_DEVICE;

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

    if (vkCreateCommandPool(outputDevice->outputDevice->device, &poolInfo, NULL, &outputDevice->outputDevice->transferCommandPool) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_COMMAND_POOL;

    VkFenceCreateInfo fenceInfo = { .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
    if (vkCreateFence(outputDevice->outputDevice->device, &fenceInfo, NULL, &outputDevice->outputDevice->barrierFence) != VK_SUCCESS) return GN_FAILED_TO_CREATE_FENCE;

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
