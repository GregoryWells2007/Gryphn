#include "gryphn/gryphn_utils.h"
#include "vulkan_physical_device.h"
#include <instance/vulkan_instance.h>
#include <presentation_queue/vulkan_queue_families.h>
#include "vulkan_device_extensions.h"

// #include "core/output_device/gryphn_physical_output_device.h"
// #include <vulkan/vulkan.h>
// #include "vulkan_output_devices.h"
// #include "presentation_queue/vulkan_swapchain.h"

GN_EXPORT gnPhysicalDevice* gnGetPhysicalDevicesFn(gnInstance* instance, uint32_t* deviceCount) {
    vkEnumeratePhysicalDevices(instance->instance->vk_instance, deviceCount, nullptr);
    if (deviceCount == 0)
        return nullptr;

    std::vector<VkPhysicalDevice> devices(*deviceCount);
    vkEnumeratePhysicalDevices(instance->instance->vk_instance, deviceCount, devices.data());
    gnPhysicalDevice* outputDevices = (gnPhysicalDevice*)malloc(sizeof(gnPhysicalDevice) * *deviceCount);

    for (int i = 0; i < *deviceCount; i++) {
        outputDevices[i].physicalDevice = new gnPlatformPhysicalDevice();
        outputDevices[i].physicalDevice->device = devices[i];

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
        outputDevices[i].name = gnCreateString(deviceProperties.deviceName);
    }

    return outputDevices;
}

GN_EXPORT gnBool gnDeviceSupportsAPIFn(const gnPhysicalDevice device) {
    //QueueFamilyIndices indices = findQueueFamilies(device.instance->instance->window_surface, device.physicalDevice->device);
    //bool swapChainAdequate = true, extensionsSupported = true;
    // bool extensionsSupported = checkDeviceExtensionSupport(deviceExtensions, device.physicalDevice->device);

    // bool swapChainAdequate = false;
    // if (extensionsSupported) {
    //     SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device.physicalOutputDevice->instance->instance->window_surface, device.physicalOutputDevice->device);
    //     swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    // }

    //VkPhysicalDeviceFeatures supportedFeatures;
    //vkGetPhysicalDeviceFeatures(device.physicalDevice->device, &supportedFeatures);

    //return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    return gnTrue;
}
