#include <vulkan/vulkan.h>
#include <output_device/vulkan_physical_device.h>
#include <output_device/vulkan_output_devices.h>
#include "vulkan_device_extensions.h"

#include <stdio.h>

gnReturnCode gnCreateOutputDeviceFn(gnOutputDevice* outputDevice, gnInstance* instance, struct gnOutputDeviceInfo_t deviceInfo) {
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

    // {
    //     QueueFamilyIndices queueFamilyIndices = findQueueFamilies(
    //             outputDevice->physicalOutputDevice->physicalOutputDevice->instance->instance->window_surface,
    //             outputDevice->physicalOutputDevice->physicalOutputDevice->device
    //     );

    //     VkCommandPoolCreateInfo poolInfo{};
    //     poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    //     poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    //     poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    //     if (vkCreateCommandPool(outputDevice->outputDevice->device, &poolInfo, nullptr, &outputDevice->outputDevice->commandPool) != VK_SUCCESS) {
    //         return GN_FAILED;
    //     }
    // }

    return GN_SUCCESS;
}

void gnWaitForDeviceFn(const gnOutputDevice* device) {
    vkDeviceWaitIdle(device->outputDevice->device);
}

void gnDestroyOutputDeviceFn(gnOutputDevice* device) {
    vkDestroyDevice(device->outputDevice->device, NULL);
    free(device->outputDevice);
}
