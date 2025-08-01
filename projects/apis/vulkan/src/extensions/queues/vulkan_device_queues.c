#include "vulkan_device_queues.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode vulkanPhysicalDeviceQueueProperties(gnPhysicalOutputDeviceHandle device, uint32_t queueFamilyCount, gnQueueFamilyProperties* queues) {
    vkGetPhysicalDeviceQueueFamilyProperties(device->physicalDevice->device, &queueFamilyCount, NULL);
    if (queues == NULL) return GN_SUCCESS;

    VkQueueFamilyProperties* queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device->physicalDevice->device, &queueFamilyCount, queueFamilies);

    for (int i = 0; i < queueFamilyCount; i++) {
        queues[i].queueCount = queueFamilies[i].queueCount;
        queues[i].queueTypeFlags = 0;

        if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT)             queues[i].queueTypeFlags |= GN_QUEUE_GRAPHICS_BIT;
        if ((queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) == VK_QUEUE_COMPUTE_BIT)               queues[i].queueTypeFlags |= GN_QUEUE_COMPUTE_BIT;
        if ((queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT)             queues[i].queueTypeFlags |= GN_QUEUE_TRANSFER_BIT;
        if ((queueFamilies[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) == VK_QUEUE_SPARSE_BINDING_BIT) queues[i].queueTypeFlags |= GN_QUEUE_SPARSE_BINDING_BIT;
        if ((queueFamilies[i].queueFlags & VK_QUEUE_PROTECTED_BIT) == VK_QUEUE_PROTECTED_BIT)           queues[i].queueTypeFlags |= GN_QUEUE_PROTECTED_BIT;
    }
    return GN_SUCCESS;
}

void getVulkanDeviceQueue(gnOutputDevice device, uint32_t queueFamily, uint32_t queueIndex, gnQueue* queue) {
    VkQueue vulkanQueue;
    vkGetDeviceQueue(device->outputDevice->device, queueFamily, queueIndex, &vulkanQueue);
    *queue = (uint64_t)vulkanQueue;
}
