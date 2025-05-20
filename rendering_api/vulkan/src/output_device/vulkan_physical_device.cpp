#include "core/output_device/gryphn_physical_output_device.h"
#include <vulkan/vulkan.h>
#include <instance/vulkan_instance.h>
#include "presentation_queue/vulkan_queue_families.h"
#include "vulkan_output_devices.h"
#include "presentation_queue/vulkan_swapchain.h"

GN_EXPORT gnPhysicalOutputDevice* gnGetPhysicalOutputDevicesFn(const gnInstance& instance, uint32_t* deviceCount) {
    vkEnumeratePhysicalDevices(instance.instance->vk_instance, deviceCount, nullptr);
    if (deviceCount == 0)
        return nullptr;

    std::vector<VkPhysicalDevice> devices(*deviceCount);
    vkEnumeratePhysicalDevices(instance.instance->vk_instance, deviceCount, devices.data());

    gnPhysicalOutputDevice* outputDevices = (gnPhysicalOutputDevice*)malloc(sizeof(gnPhysicalOutputDevice) * *deviceCount);

    for (int i = 0; i < *deviceCount; i++) {
        outputDevices[i].physicalOutputDevice = new gnPlatformPhysicalOutputDevice();
        outputDevices[i].physicalOutputDevice->device = devices[i];
        outputDevices[i].physicalOutputDevice->instance = const_cast<gnInstance*>(&instance);

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
        outputDevices[i].outputDeviceName = gnCreateString(deviceProperties.deviceName);
    }

    return outputDevices;
}

GN_EXPORT bool gnDeviceSupportsAPIFn(const gnPhysicalOutputDevice& device) {
    QueueFamilyIndices indices = findQueueFamilies(device.physicalOutputDevice->instance->instance->window_surface, device.physicalOutputDevice->device);
    bool extensionsSupported = checkDeviceExtensionSupport(deviceExtensions, device.physicalOutputDevice->device);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device.physicalOutputDevice->instance->instance->window_surface, device.physicalOutputDevice->device);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(device.physicalOutputDevice->device, &supportedFeatures);

    return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}
