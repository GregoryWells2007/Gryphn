#include "core/output_device/gryphn_physical_output_device.h"
#include <vulkan/vulkan.h>
#include <instance/vulkan_instance.h>
#include "presentation_queue/vulkan_queue_families.h"
#include "vulkan_output_devices.h"
#include "presentation_queue/vulkan_swapchain.h"

// gnPhysicalOutputDevice::gnPhysicalOutputDevice() {
//     physicalOutputDevice = new gnPlatformPhysicalOutputDevice();
// }

GN_EXPORT gnList<gnPhysicalOutputDevice> gnGetPhysicalOutputDevicesFn(const gnInstance& instance) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance.instance->vk_instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        // throw std::runtime_error("failed to find any physical devices");
        // TODO: why am I error checking for myself I can read the size of a list can't I
        return gnCreateList<gnPhysicalOutputDevice>();
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance.instance->vk_instance, &deviceCount, devices.data());


    gnList<gnPhysicalOutputDevice> outputDevices = gnCreateList<gnPhysicalOutputDevice>();

    for (int i = 0; i < deviceCount; i++) {
        gnPhysicalOutputDevice newOutputDevice = gnPhysicalOutputDevice();
        newOutputDevice.physicalOutputDevice = new gnPlatformPhysicalOutputDevice();
        newOutputDevice.physicalOutputDevice->device = devices[i];
        newOutputDevice.physicalOutputDevice->instance = const_cast<gnInstance*>(&instance);

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
        newOutputDevice.outputDeviceName = gnCreateString(deviceProperties.deviceName);

        gnListAdd(outputDevices, newOutputDevice);
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
