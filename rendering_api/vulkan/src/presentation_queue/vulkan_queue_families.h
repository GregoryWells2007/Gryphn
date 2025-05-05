#pragma once
#include <gryphn/gryphn_utils.h>
#include <vulkan/vulkan.h>
#include <vector>
#include "optional"
#include "set"

// quere familys shit, have zero fucking clue what this does, well I kinda do but I dont 100% know like I couldn't explain it
// it does work tho
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

static QueueFamilyIndices findQueueFamilies(const VkSurfaceKHR& surface, const VkPhysicalDevice& device) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if (presentSupport)
            indices.presentFamily = i;

        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphicsFamily = i;

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}
