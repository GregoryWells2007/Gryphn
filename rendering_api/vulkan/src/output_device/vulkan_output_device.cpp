#include <vulkan/vulkan.h>
// #include "presentation_queue/vulkan_queue_families.h"
// #include "presentation_queue/vulkan_swapchain.h"
#include "vulkan_device_extensions.h"
#include "vulkan_output_devices.h"
#include <instance/vulkan_instance.h>
#include "vulkan_physical_device.h"
#include "presentation_queue/vulkan_queue_families.h"
// #include <set>

GN_EXPORT gnReturnCode gnRegisterOutputDeviceFn(gnOutputDevice* outputDevice, gnInstance* instance, const gnPhysicalDevice physicalDevice) {
    if (outputDevice->outputDevice == nullptr) outputDevice->outputDevice = new gnPlatformOutputDevice();

    //instance.instance->window_surface,
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice.physicalDevice->device);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    //indices.presentFamily.value()
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();


    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    const char* validation_layers[1] = { "VK_LAYER_KHRONOS_validation" };

    createInfo.enabledLayerCount = 1;
    createInfo.ppEnabledLayerNames = validation_layers;

    if (vkCreateDevice(physicalDevice.physicalDevice->device, &createInfo, nullptr, &outputDevice->outputDevice->device) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_DEVICE;
    }

    vkGetDeviceQueue(outputDevice->outputDevice->device, indices.graphicsFamily.value(), 0, &outputDevice->outputDevice->graphicsQueue);
    // vkGetDeviceQueue(outputDevice->outputDevice->device, indices.presentFamily.value(), 0, &outputDevice->outputDevice->presentQueue);
    // outputDevice->physicalOutputDevice = const_cast<gnPhysicalOutputDevice*>(&physicalDevice);

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

GN_EXPORT void gnWaitForDeviceFn(const gnOutputDevice& device) {
    vkDeviceWaitIdle(device.outputDevice->device);
}

GN_EXPORT void gnDestroyOutputDeviceFn(gnOutputDevice& device) {
    // vkDestroyCommandPool(device.outputDevice->device, device.outputDevice->commandPool, nullptr);
    vkDestroyDevice(device.outputDevice->device, nullptr);
}
