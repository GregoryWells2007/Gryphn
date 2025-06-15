#include <core/window_surface/gryphn_surface_create_functions.h>
#include <instance/vulkan_instance.h>
#include "vulkan_surface.h"
#include <output_device/vulkan_physical_device.h>
#include <stdio.h>


#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
#include <vulkan/vulkan_xlib.h>
#include <X11/Xlib.h>
gnReturnCode gnCreateX11WindowSurfaceFn(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnX11WindowSurfaceInfo createInfo) {
    windowSurface->windowSurface = malloc(sizeof(struct gnPlatformWindowSurface_t));
    VkXlibSurfaceCreateInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    info.dpy = createInfo.display;
    info.window = createInfo.window;

    VkResult result = vkCreateXlibSurfaceKHR(instance->instance->vk_instance, &info, NULL, &windowSurface->windowSurface->surface);
    if (result != VK_SUCCESS)
        return GN_FAILED_TO_ATTACH_WINDOW;
    return GN_SUCCESS;
}
#endif

#ifdef GN_WINFDOW_WAYLAND
#include <vulkan/vulkan_wayland.h>
gnReturnCode gnCreateWaylandWindowSurface(struct gnWindowSurface_t* windowSurface, gnInstanceHandle instance, struct gnWaylandWindowSurfaceInfo_t createInfo) {
    windowSurface->windowSurface = malloc(sizeof(struct gnPlatformWindowSurface_t));
    VkWaylandSurfaceCreateInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    info.display = createInfo.display;
    info.surface = createInfo.surface;

    VkResult result = vkCreateWaylandSurfaceKHR(instance->instance->vk_instance, &info, NULL, &windowSurface->windowSurface->surface);
    if (result != VK_SUCCESS)
        return GN_FAILED_TO_ATTACH_WINDOW;
    return GN_SUCCESS;
}
#endif
#endif

#ifdef GN_PLATFORM_WINDOWS
#include "vulkan/vulkan_win32.h"
gnReturnCode gnCreateWin32WindowSurface(struct gnWindowSurface_t* windowSurface, gnInstanceHandle instance, struct gnWin32WindowSurfaceInfo_t createInfo) {
    windowSurface->windowSurface = malloc(sizeof(struct gnPlatformWindowSurface_t));
    VkWin32SurfaceCreateInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    info.hwnd = createInfo.window;
    info.hinstance = createInfo.instance;

    VkResult result = vkCreateWin32SurfaceKHR(instance->instance->vk_instance, &info, NULL, &windowSurface->windowSurface->surface);
    if (result != VK_SUCCESS)
        return GN_FAILED_TO_ATTACH_WINDOW;
    return GN_SUCCESS;
}
#endif


void gnDestroyWindowSurfaceFn(struct gnWindowSurface_t* windowSurface) {
    vkDestroySurfaceKHR(windowSurface->instance->instance->vk_instance, windowSurface->windowSurface->surface, NULL);
}

struct gnSurfaceFormat_t* vkGetSurfaceFormats(
    struct gnWindowSurface_t* windowSurface, struct gnPhysicalDevice_t device, uint32_t* formatCount
) {
    struct gnSurfaceFormat_t* formats = NULL;

    vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalDevice->device, windowSurface->windowSurface->surface, formatCount, NULL);
    formats = malloc(sizeof(struct gnSurfaceFormat_t) * *formatCount);
    VkSurfaceFormatKHR* vkFormats = malloc(sizeof(VkSurfaceFormatKHR) * *formatCount);;

    if (*formatCount > 0) {
        vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalDevice->device, windowSurface->windowSurface->surface, formatCount, vkFormats);
        for (int i = 0; i < *formatCount; i++) {
            switch (vkFormats[i].format) {
            case VK_FORMAT_B8G8R8A8_SRGB: { formats[i].format = GN_FORMAT_BGRA8_SRGB; break; }
            default: break;
            }

            switch (vkFormats[i].colorSpace) {
            case VK_COLOR_SPACE_SRGB_NONLINEAR_KHR: { formats[i].colorSpace = GN_COLOR_SPACE_SRGB_NONLINEAR; break; }
            default: break;
            }
        }
    }

    return formats;
}

gnSurfaceDetails gnGetSurfaceDetailsFn(
    gnWindowSurfaceHandle windowSurface, gnPhysicalDevice device
) {
    gnSurfaceDetails surfaceDetails;
    surfaceDetails.formats = vkGetSurfaceFormats(windowSurface, device, &surfaceDetails.formatCount);

    VkSurfaceCapabilitiesKHR details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.physicalDevice->device, windowSurface->windowSurface->surface, &details);

    surfaceDetails.minImageCount = details.minImageCount;
    surfaceDetails.maxImageCount = details.maxImageCount;

    surfaceDetails.minImageSize = (gnUInt2){ details.minImageExtent.width, details.minImageExtent.height };
    surfaceDetails.maxImageSize = (gnUInt2){ details.maxImageExtent.width, details.maxImageExtent.height };
    surfaceDetails.currentSize = (gnUInt2){ details.currentExtent.width, details.currentExtent.height };

    return surfaceDetails;
}


VkFormat vkGryphnFormatToVulkanFormat(gnImageFormat format) {
    switch (format) {
    case GN_FORMAT_BGRA8_SRGB: return VK_FORMAT_B8G8R8A8_SRGB;
    case GN_FORMAT_RGBA8_SRGB: return VK_FORMAT_R8G8B8A8_SRGB;
    default: return VK_FORMAT_UNDEFINED;
    }
}
VkColorSpaceKHR vkGryphnColorSpaceToVulkanColorSpace(gnColorSpace colorSpace) {
    switch (colorSpace) {
    case GN_COLOR_SPACE_SRGB_NONLINEAR: { return VK_COLOR_SPACE_SRGB_NONLINEAR_KHR; }
    }
}
