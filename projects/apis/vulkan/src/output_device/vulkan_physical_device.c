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

gnPhysicalDevice* getPhysicalDevices(gnInstanceHandle instance, uint32_t* deviceCount) {
    vkEnumeratePhysicalDevices(instance->instance->vk_instance, deviceCount, NULL);
    if (deviceCount == 0)
        return NULL;

    VkPhysicalDevice* physicalDevices = malloc(sizeof(VkPhysicalDevice) * *deviceCount);
    vkEnumeratePhysicalDevices(instance->instance->vk_instance, deviceCount, physicalDevices);
    gnPhysicalDevice* outputDevices = (gnPhysicalDevice*)malloc(sizeof(gnPhysicalDevice) * *deviceCount);

    for (int i = 0; i < *deviceCount; i++) {
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

        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &outputDevices[i]->queueProperties.queueCount, NULL);

        VkQueueFamilyProperties* queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * outputDevices[i]->queueProperties.queueCount);
        outputDevices[i]->queueProperties.queueProperties = malloc(sizeof(gnQueueProperties) * outputDevices[i]->queueProperties.queueCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &outputDevices[i]->queueProperties.queueCount, queueFamilies);
        for (int c = 0; c < outputDevices[i]->queueProperties.queueCount; c++) {
            outputDevices[i]->queueProperties.queueProperties[i].queueCount = queueFamilies[i].queueCount;

            gnQueueTypeFlags finalQueueType = 0;
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) finalQueueType |= GN_QUEUE_GRAPHICS;
            if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) finalQueueType |= GN_QUEUE_COMPUTE;
            if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) finalQueueType |= GN_QUEUE_TRANSFER;
            if (queueFamilies[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) finalQueueType |= GN_QUEUE_SPARSE_BINDING;
            outputDevices[i]->queueProperties.queueProperties[i].queueType = finalQueueType;
        }

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

gnBool queueCanPresentToSurface(gnPhysicalDevice device, uint32_t queueIndex, gnWindowSurfaceHandle windowSurface) {
    VkBool32 supportsPresent = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(device->physicalDevice->device, queueIndex, windowSurface->windowSurface->surface, &supportsPresent);
    if (supportsPresent)
        return gnTrue;
    return gnFalse;
}
