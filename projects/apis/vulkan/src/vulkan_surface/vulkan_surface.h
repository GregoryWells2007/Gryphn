#pragma once
#include <window_surface/gryphn_surface.h>
#include <window_surface/gryphn_surface_create_functions.h>
#include <vulkan/vulkan.h>

typedef struct gnPlatformWindowSurface_t {
    VkSurfaceKHR surface;
    uint32_t presentQueueIndex;
} gnPlatformWindowSurface;

VkFormat vkGryphnFormatToVulkanFormat(gnImageFormat format);
VkColorSpaceKHR vkGryphnColorSpaceToVulkanColorSpace(gnColorSpace colorSpace);

#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
gnReturnCode createX11WindowSurface(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnX11WindowSurfaceInfo createInfo);
#endif
#endif
#ifdef GN_PLATFORM_MACOS
gnReturnCode createMacOSWindowSurface(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnMacOSWindowSurfaceInfo createInfo);
#endif

gnSurfaceDetails getSurfaceDetails(gnWindowSurfaceHandle windowSurface, gnPhysicalDevice device);
void destroyWindowSurface(gnWindowSurface windowSurface);
