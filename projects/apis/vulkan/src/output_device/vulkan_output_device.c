#include <vulkan/vulkan.h>
#include <output_device/vulkan_physical_device.h>
#include <output_device/vulkan_output_devices.h>
#include "vulkan_device_extensions.h"
#include "instance/gryphn_instance.h"
#include "commands/command_buffer/vulkan_command_buffer.h"

gnReturnCode createOutputDevice(gnOutputDeviceHandle outputDevice, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo) {
    outputDevice->outputDevice = malloc(sizeof(gnPlatformOutputDevice));

    VkDeviceQueueCreateInfo* queueCreateInfos = malloc(sizeof(VkDeviceQueueCreateInfo) * deviceInfo.queueInfoCount);
    float queuePriority = 1.0f;
    for (int i = 0; i < deviceInfo.queueInfoCount; i++) {
        queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfos[i].flags = 0;
        queueCreateInfos[i].queueFamilyIndex = deviceInfo.queueInfos[i].queueIndex;
        queueCreateInfos[i].queueCount = deviceInfo.queueInfos[i].queueCount;
        queueCreateInfos[i].pQueuePriorities = &queuePriority;
    }

    VkPhysicalDeviceFeatures deviceFeatures = {
        .samplerAnisotropy = VK_TRUE
    };



    VkDeviceCreateInfo deviceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = deviceInfo.queueInfoCount,
        .pQueueCreateInfos = queueCreateInfos,
        .pEnabledFeatures = &deviceFeatures
    };
    deviceCreateInfo.ppEnabledExtensionNames = vkGetGryphnDeviceExtensions(&deviceCreateInfo.enabledExtensionCount, deviceInfo.physicalDevice.physicalDevice->device);

    outputDevice->outputDevice->enabledOversizedDescriptorPools = gnFalse;
    for (int i = 0; i < deviceCreateInfo.enabledExtensionCount; i++)
        if (strcmp(deviceCreateInfo.ppEnabledExtensionNames[i], VK_NV_DESCRIPTOR_POOL_OVERALLOCATION_EXTENSION_NAME) == 0) outputDevice->outputDevice->enabledOversizedDescriptorPools = gnTrue;

    if (instance->debugger == NULL)
        deviceCreateInfo.enabledLayerCount = 0;
    else {
        const char* validation_layers[1] = { "VK_LAYER_KHRONOS_validation" };
        deviceCreateInfo.enabledLayerCount = 1;
        deviceCreateInfo.ppEnabledLayerNames = validation_layers;
    }

    if (vkCreateDevice(deviceInfo.physicalDevice.physicalDevice->device, &deviceCreateInfo, NULL, &outputDevice->outputDevice->device) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_DEVICE;

    outputDevice->outputDevice->queues = malloc(sizeof(VkQueue) * deviceInfo.queueInfoCount);
    for (int i = 0; i < deviceInfo.queueInfoCount; i++) {
        vkGetDeviceQueue(outputDevice->outputDevice->device, deviceInfo.queueInfos[i].queueIndex, 0, &outputDevice->outputDevice->queues[i]);
    }

    uint32_t queueCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(
        deviceInfo.physicalDevice.physicalDevice->device,
        &queueCount,
        NULL
    );

    VkQueueFamilyProperties* queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * queueCount);
    vkGetPhysicalDeviceQueueFamilyProperties(
        deviceInfo.physicalDevice.physicalDevice->device,
        &queueCount,
        queueFamilies
    );

    uint32_t transferQueueIndex = 0;
    for (int i = 0; i < queueCount; i++) {
        if ((queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT) {
            transferQueueIndex = i;
            vkGetDeviceQueue(outputDevice->outputDevice->device, deviceInfo.queueInfos[i].queueIndex, 0, &outputDevice->outputDevice->transferQueue);
            break;
        }
    }

    VkCommandPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = transferQueueIndex
    };

    if (vkCreateCommandPool(outputDevice->outputDevice->device, &poolInfo, NULL, &outputDevice->outputDevice->transferCommandPool) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_COMMAND_POOL;

    free(queueCreateInfos);
    free(queueFamilies);

    return GN_SUCCESS;
}

void waitForDevice(const gnOutputDeviceHandle device) {
    vkDeviceWaitIdle(device->outputDevice->device);
}

void destroyOutputDevice(gnOutputDeviceHandle device) {
    vkDestroyCommandPool(device->outputDevice->device, device->outputDevice->transferCommandPool, NULL);
    vkDestroyDevice(device->outputDevice->device, NULL);
    free(device->outputDevice);
}


VkCommandBuffer gnBeginVulkanTransferOperation(gnDevice device) {
    return VkBeginTransferOperation(device->outputDevice->device, device->outputDevice->transferCommandPool);
}
void gnEndVulkanTransferOperation(gnDevice device, VkCommandBuffer buffer) {
    VkEndTransferOperation(buffer, device->outputDevice->transferCommandPool, device->outputDevice->transferQueue, device->outputDevice->device);
}
