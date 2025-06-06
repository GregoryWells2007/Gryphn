#include <vulkan/vulkan.h>
#include <output_device/vulkan_physical_device.h>
#include <output_device/vulkan_output_devices.h>
#include "vulkan_device_extensions.h"
#include "core/instance/gryphn_instance.h"

#include <stdio.h>

gnReturnCode gnCreateOutputDeviceFn(gnOutputDeviceHandle outputDevice, gnInstanceHandle instance, struct gnOutputDeviceInfo_t deviceInfo) {
    outputDevice->outputDevice = malloc(sizeof(gnPlatformOutputDevice));

    VkDeviceQueueCreateInfo* queueCreateInfos = malloc(sizeof(VkDeviceQueueCreateInfo) * deviceInfo.queueInfoCount);
    float queuePriority = 1.0f;
    for (int i = 0; i < deviceInfo.queueInfoCount; i++) {
        queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfos[i].queueFamilyIndex = deviceInfo.queueInfos[i].queueIndex;
        queueCreateInfos[i].queueCount = deviceInfo.queueInfos[i].queueCount;
        queueCreateInfos[i].pQueuePriorities = &queuePriority;
    }

    VkPhysicalDeviceFeatures deviceFeatures = {};

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = deviceInfo.queueInfoCount;
    createInfo.pQueueCreateInfos = queueCreateInfos;
    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = deviceExtensionCount;
    createInfo.ppEnabledExtensionNames = deviceExtensions;

    if (instance->debugger == NULL)
        createInfo.enabledLayerCount = 0;
    else {
        const char* validation_layers[1] = { "VK_LAYER_KHRONOS_validation" };
        createInfo.enabledLayerCount = 1;
        createInfo.ppEnabledLayerNames = validation_layers;
    }

    if (vkCreateDevice(deviceInfo.physicalDevice.physicalDevice->device, &createInfo, NULL, &outputDevice->outputDevice->device) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_DEVICE;
    }

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

    if (vkCreateCommandPool(outputDevice->outputDevice->device, &poolInfo, NULL, &outputDevice->outputDevice->transferCommandPool) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_COMMAND_POOL;
    }

    return GN_SUCCESS;
}

void gnWaitForDeviceFn(const gnOutputDeviceHandle device) {
    vkDeviceWaitIdle(device->outputDevice->device);
}

void gnDestroyOutputDeviceFn(gnOutputDeviceHandle device) {
    vkDestroyCommandPool(device->outputDevice->device, device->outputDevice->transferCommandPool, NULL);
    vkDestroyDevice(device->outputDevice->device, NULL);
    free(device->outputDevice);
}
