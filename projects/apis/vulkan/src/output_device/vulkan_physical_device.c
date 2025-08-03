#include "vulkan_physical_device.h"
#include <instance/vulkan_instance.h>
#include <output_device/vulkan_device_extensions.h>
#include <vulkan_surface/vulkan_surface.h>

gnMultisampleCountFlags vkSampleCountToGryphn(VkSampleCountFlags counts) {
    gnMultisampleCountFlags sampleCount = 0;
    if ((counts & VK_SAMPLE_COUNT_64_BIT) == VK_SAMPLE_COUNT_64_BIT) { sampleCount |= GN_SAMPLE_BIT_64; }
    if ((counts & VK_SAMPLE_COUNT_32_BIT) == VK_SAMPLE_COUNT_32_BIT) { sampleCount |= GN_SAMPLE_BIT_32; }
    if ((counts & VK_SAMPLE_COUNT_16_BIT) == VK_SAMPLE_COUNT_16_BIT) { sampleCount |= GN_SAMPLE_BIT_16; }
    if ((counts & VK_SAMPLE_COUNT_8_BIT) == VK_SAMPLE_COUNT_8_BIT) { sampleCount |= GN_SAMPLE_BIT_8; }
    if ((counts & VK_SAMPLE_COUNT_4_BIT) == VK_SAMPLE_COUNT_4_BIT) { sampleCount |= GN_SAMPLE_BIT_4; }
    if ((counts & VK_SAMPLE_COUNT_2_BIT) == VK_SAMPLE_COUNT_2_BIT) { sampleCount |= GN_SAMPLE_BIT_2; }
    if ((counts & VK_SAMPLE_COUNT_1_BIT) == VK_SAMPLE_COUNT_1_BIT) { sampleCount |= GN_SAMPLE_BIT_1; }
    return sampleCount;
}

#include <stdio.h>

VkSampleCountFlags gnSampleCountToVulkan(gnMultisampleCountFlags counts) {
    VkSampleCountFlags sampleCount = 0;

    if ((counts & GN_SAMPLE_BIT_64) == GN_SAMPLE_BIT_64) { sampleCount |= VK_SAMPLE_COUNT_64_BIT; }
    if ((counts & GN_SAMPLE_BIT_32) == GN_SAMPLE_BIT_32) { sampleCount |= VK_SAMPLE_COUNT_32_BIT; }
    if ((counts & GN_SAMPLE_BIT_16) == GN_SAMPLE_BIT_16) { sampleCount |= VK_SAMPLE_COUNT_16_BIT; }
    if ((counts & GN_SAMPLE_BIT_8) == GN_SAMPLE_BIT_8) { sampleCount |= VK_SAMPLE_COUNT_8_BIT; }
    if ((counts & GN_SAMPLE_BIT_4) == GN_SAMPLE_BIT_4) { sampleCount |= VK_SAMPLE_COUNT_4_BIT; }
    if ((counts & GN_SAMPLE_BIT_2) == GN_SAMPLE_BIT_2) { sampleCount |= VK_SAMPLE_COUNT_2_BIT; }
    if ((counts & GN_SAMPLE_BIT_1) == GN_SAMPLE_BIT_1) { sampleCount |= VK_SAMPLE_COUNT_1_BIT; }

    return sampleCount;
}

void vulkanLoadNeededQueues(VkPhysicalDevice vulkanDevice, gnPhysicalDevice gryphnDevice) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vulkanDevice, &queueFamilyCount, NULL);
    VkQueueFamilyProperties* queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(vulkanDevice, &queueFamilyCount, queueFamilies);

    gryphnDevice->physicalDevice->neededQueues = malloc(sizeof(vulkanNeededQueue) * queueFamilyCount);
    for (uint32_t c = 0; c < queueFamilyCount; c++) {
        gnBool hasNeededQueue = GN_FALSE;

        if ((queueFamilies[c].queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT)
            hasNeededQueue = GN_TRUE;
        if ((queueFamilies[c].queueFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT)
            hasNeededQueue = GN_TRUE;

        if (hasNeededQueue) {
            vulkanNeededQueue neededQueue = {
                .queueIndex = c,
                .createFlags = 0,
                .usedForPresent = GN_FALSE
            };
            if ((queueFamilies[c].queueFlags & VK_QUEUE_GRAPHICS_BIT)) neededQueue.createFlags |= VK_QUEUE_GRAPHICS_BIT;
            if ((queueFamilies[c].queueFlags & VK_QUEUE_TRANSFER_BIT)) neededQueue.createFlags |= VK_QUEUE_TRANSFER_BIT;

            gryphnDevice->physicalDevice->neededQueues[gryphnDevice->physicalDevice->neededQueueCount] = neededQueue;
            gryphnDevice->physicalDevice->neededQueueCount++;
        }
    }

    free(queueFamilies);
}

gnPhysicalDevice* getPhysicalDevices(gnInstanceHandle instance, uint32_t* deviceCount) {
    vkEnumeratePhysicalDevices(instance->instance->vk_instance, deviceCount, NULL);
    if (deviceCount == 0)
        return NULL;

    VkPhysicalDevice* physicalDevices = malloc(sizeof(VkPhysicalDevice) * *deviceCount);
    vkEnumeratePhysicalDevices(instance->instance->vk_instance, deviceCount, physicalDevices);
    gnPhysicalDevice* outputDevices = (gnPhysicalDevice*)malloc(sizeof(gnPhysicalDevice) * *deviceCount);

    for (uint32_t i = 0; i < *deviceCount; i++) {
        outputDevices[i] = malloc(sizeof(gnPhysicalOutputDevice_t));
        outputDevices[i]->physicalDevice = malloc(sizeof(struct gnPlatformPhysicalDevice_t));
        outputDevices[i]->physicalDevice->device = physicalDevices[i];

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevices[i], &deviceProperties);
        outputDevices[i]->properties.name = gnCreateString(deviceProperties.deviceName);
        switch(deviceProperties.deviceType) {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER: outputDevices[i]->properties.deviceType = GN_EXTERNAL_DEVICE;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: outputDevices[i]->properties.deviceType = GN_INTEGRATED_DEVICE;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: outputDevices[i]->properties.deviceType = GN_DEDICATED_DEVICE;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: outputDevices[i]->properties.deviceType = GN_INTEGRATED_DEVICE;
        case VK_PHYSICAL_DEVICE_TYPE_CPU: outputDevices[i]->properties.deviceType = GN_INTEGRATED_DEVICE;
        case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM: outputDevices[i]->properties.deviceType = GN_INTEGRATED_DEVICE;
        }

        if (instance->enabledExtensions[GN_EXT_QUEUES] == GN_FALSE)
            vulkanLoadNeededQueues(physicalDevices[i], outputDevices[i]);


        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDeviceProperties);
        outputDevices[i]->features.maxColorSamples = vkSampleCountToGryphn(physicalDeviceProperties.limits.framebufferColorSampleCounts);
        outputDevices[i]->features.maxDepthSamples = vkSampleCountToGryphn(physicalDeviceProperties.limits.framebufferDepthSampleCounts);
        outputDevices[i]->features.maxMemoryAllocations = physicalDeviceProperties.limits.maxMemoryAllocationCount;
        outputDevices[i]->features.maxPushConstantSize = physicalDeviceProperties.limits.maxPushConstantsSize;
    }
    free(physicalDevices);

    return outputDevices;
}

gnBool deviceCanPresentToSurface(gnPhysicalDevice device, gnWindowSurface surface) {
    gnBool foundQueue = GN_FALSE;
    for (uint32_t i = 0; i < device->physicalDevice->neededQueueCount; i++) {
        VkBool32 supportsPresent = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(device->physicalDevice->device, device->physicalDevice->neededQueues[i].queueIndex, surface->windowSurface->surface, &supportsPresent);
        if (supportsPresent) {
            device->physicalDevice->neededQueues[i].usedForPresent = GN_TRUE;
            foundQueue = GN_TRUE;
            break;
        }
        surface->windowSurface->presentQueueIndex = i;
    }

    if (!foundQueue) {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device->physicalDevice->device, &queueFamilyCount, NULL);

        for (uint32_t i = 0; i < queueFamilyCount; i++) {
            VkBool32 supportsPresent = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(device->physicalDevice->device, i, surface->windowSurface->surface, &supportsPresent);
            if (supportsPresent) {
                device->physicalDevice->neededQueues[device->physicalDevice->neededQueueCount] = (vulkanNeededQueue){
                    .queueIndex = i,
                    .createFlags = 0,
                    .usedForPresent = GN_TRUE
                };
                foundQueue = GN_TRUE;
                surface->windowSurface->presentQueueIndex = device->physicalDevice->neededQueueCount;
                device->physicalDevice->neededQueueCount++;
                break;
            }
        }
    }

    return foundQueue;
}
