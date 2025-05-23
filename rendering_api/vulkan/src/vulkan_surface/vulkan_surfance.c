#include <instance/vulkan_instance.h>
#include "vulkan_surface.h"

#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
#include <vulkan/vulkan_xlib.h>
#include <X11/Xlib.h>
gnReturnCode gnCreateX11WindowSurfaceFn(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnX11WindowSurfaceInfo_t createInfo) {
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
gnReturnCode gnCreateWaylandWindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnWaylandWindowSurfaceInfo_t createInfo) {
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
gnReturnCode gnCreateWin32WindowSurface(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnWin32WindowSurfaceInfo_t createInfo) {
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
