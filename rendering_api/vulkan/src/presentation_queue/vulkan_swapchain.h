// #pragma once
// #include <vulkan/vulkan.h>
// #include <gryphn/gryphn_utils.h>
// #include <cstdint> // Necessary for uint32_t
// #include <limits> // Necessary for std::numeric_limits
// #include <algorithm> // Necessary for std::clamp
// #include "vector"
// #include "set"
// #include <iostream>

// const std::vector<const char*> deviceExtensions = {
//     VK_KHR_SWAPCHAIN_EXTENSION_NAME,
//     "VK_KHR_portability_subset"
// };

// static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
//     for (const auto& availableFormat : availableFormats) {
//         if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
//             return availableFormat;
//         }
//     }

//     return availableFormats[0];
// }

// static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
//     for (const auto& availablePresentMode : availablePresentModes) {
//         if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
//             return availablePresentMode;
//         }
//     }

//     return VK_PRESENT_MODE_FIFO_KHR;
// }

// static VkExtent2D chooseSwapExtent(gnVec2 size, const VkSurfaceCapabilitiesKHR& capabilities) {
//     if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
//         return capabilities.currentExtent;
//     } else {
//         // int width, height;
//         // glfwGetFramebufferSize(window, &width, &height);

//         VkExtent2D actualExtent = {
//             static_cast<uint32_t>(size.x),
//             static_cast<uint32_t>(size.y)
//         };

//         actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
//         actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

//         return actualExtent;
//     }
// }

// static bool checkDeviceExtensionSupport(std::vector<const char*> deviceExtensions, const VkPhysicalDevice& device) {
//     uint32_t extensionCount;
//     vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

//     std::vector<VkExtensionProperties> availableExtensions(extensionCount);
//     vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

//     std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

//     for (const auto& extension : availableExtensions) {
//         requiredExtensions.erase(extension.extensionName);
//     }

//     return requiredExtensions.empty();
// }

// struct SwapChainSupportDetails {
//     VkSurfaceCapabilitiesKHR capabilities;
//     std::vector<VkSurfaceFormatKHR> formats;
//     std::vector<VkPresentModeKHR> presentModes;
// };

// static SwapChainSupportDetails querySwapChainSupport(const VkSurfaceKHR& surface, const VkPhysicalDevice& device) {
//     SwapChainSupportDetails details;

//     vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

//     uint32_t formatCount;
//     vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

//     if (formatCount != 0) {
//         details.formats.resize(formatCount);
//         vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
//     }

//     uint32_t presentModeCount;
//     vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

//     if (presentModeCount != 0) {
//         details.presentModes.resize(presentModeCount);
//         vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
//     }

//     return details;
// }
