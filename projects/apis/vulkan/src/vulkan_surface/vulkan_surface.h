#pragma once
#include <window_surface/gryphn_surface.h>
#include <vulkan/vulkan.h>

typedef struct gnPlatformWindowSurface_t {
    VkSurfaceKHR surface;
} gnPlatformWindowSurface;

VkFormat vkGryphnFormatToVulkanFormat(gnImageFormat format);
VkColorSpaceKHR vkGryphnColorSpaceToVulkanColorSpace(gnColorSpace colorSpace);
