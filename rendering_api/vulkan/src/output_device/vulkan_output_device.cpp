#include <vulkan/vulkan.h>
#include "presentation_queue/vulkan_queue_families.h"
#include "presentation_queue/vulkan_swapchain.h"
#include "vulkan_output_devices.h"
#include <instance/vulkan_instance.h>
#include "set"

GN_EXPORT gnReturnCode gnRegisterOutputDeviceFn(gnOutputDevice* outputDevice, const gnInstance& instance, const gnPhysicalOutputDevice& physicalDevice) {
    if (outputDevice->outputDevice == nullptr) outputDevice->outputDevice = new gnPlatformOutputDevice();

    QueueFamilyIndices indices = findQueueFamilies(instance.instance->window_surface, physicalDevice.physicalOutputDevice->device);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

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

    if (instance.debugger) {
        auto validation_layers = instance.debugger->debug_layers;

        gnList<const char*> validation_layers_c = gnCreateList<const char*>();
        for (int i = 0; i < gnListLength(validation_layers); i++)
            gnListAdd(validation_layers_c, gnToCString(validation_layers[i]));

        createInfo.enabledLayerCount = static_cast<uint32_t>(gnListLength(validation_layers_c));
        createInfo.ppEnabledLayerNames = gnListData(validation_layers_c);
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice.physicalOutputDevice->device, &createInfo, nullptr, &outputDevice->outputDevice->device) != VK_SUCCESS) {
        return GN_FAILED;
    }

    vkGetDeviceQueue(outputDevice->outputDevice->device, indices.graphicsFamily.value(), 0, &outputDevice->outputDevice->graphicsQueue);
    vkGetDeviceQueue(outputDevice->outputDevice->device, indices.presentFamily.value(), 0, &outputDevice->outputDevice->presentQueue);
    outputDevice->physicalOutputDevice = const_cast<gnPhysicalOutputDevice*>(&physicalDevice);

    {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(
                outputDevice->physicalOutputDevice->physicalOutputDevice->instance->instance->window_surface,
                outputDevice->physicalOutputDevice->physicalOutputDevice->device
        );

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if (vkCreateCommandPool(outputDevice->outputDevice->device, &poolInfo, nullptr, &outputDevice->outputDevice->commandPool) != VK_SUCCESS) {
            return GN_FAILED;
        }
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnWaitForDeviceFn(const gnOutputDevice& device) {
    vkDeviceWaitIdle(device.outputDevice->device);
}

GN_EXPORT void gnDestroyOutputDeviceFn(gnOutputDevice& device) {
    vkDestroyCommandPool(device.outputDevice->device, device.outputDevice->commandPool, nullptr);
    vkDestroyDevice(device.outputDevice->device, nullptr);
}
