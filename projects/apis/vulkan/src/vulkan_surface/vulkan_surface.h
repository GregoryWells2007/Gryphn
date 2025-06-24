#pragma once
#include <window_surface/gryphn_surface.h>
#include <vulkan/vulkan.h>

typedef struct gnPlatformWindowSurface_t {
    VkSurfaceKHR surface;
} gnPlatformWindowSurface;

VkFormat vkGryphnFormatToVulkanFormat(gnImageFormat format);
VkColorSpaceKHR vkGryphnColorSpaceToVulkanColorSpace(gnColorSpace colorSpace);

#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
gnReturnCode createX11WindowSurface(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnX11WindowSurfaceInfo createInfo);
#endif
#endif

gnSurfaceDetails getSurfaceDetails(gnWindowSurfaceHandle windowSurface, gnPhysicalDevice device);
void destroyWindowSurface(gnWindowSurface windowSurface);
