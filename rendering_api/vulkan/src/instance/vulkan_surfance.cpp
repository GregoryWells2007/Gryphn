#include "vulkan_instance.h"

#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
#include <vulkan/vulkan_xlib.h>
#include <X11/Xlib.h>

GN_EXPORT gnReturnCode gnCreateX11WindowSurfaceFn(gnInstance& instance, Display* display, Window* window) {
    VkXlibSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    info.dpy = display;
    info.window = window;

    VkResult result = vkCreateXlibSurfaceKHR(instance.instance->vk_instance, &info, nullptr, &instance.instance->window_surface);
    if (result != VK_SUCCESS)
        return gnReturnError(GN_FAILED_CREATE_WINDOW_SURFACE, result);
    return GN_SUCCESS;
}
#endif

#ifdef GN_WINFDOW_WAYLAND
#include <vulkan/vulkan_wayland.h>
#include <wayland-client.h>
GN_EXPORT gnReturnCode gnCreateWaylandWindowSurfaceFn(gnInstance& instance, wl_display* display, wl_surface* surface) {
    VkWaylandSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    info.display = display;
    info.surface = surface;

    VkSurfaceKHR surface;
    VkResult result = vkCreateWaylandSurfaceKHR(instance.instance->vk_instance, &info, nullptr, &instance.instance->window_surface);
    if (result != VK_SUCCESS)
        return gnReturnError(GN_FAILED_CREATE_WINDOW_SURFACE, result);
    return GN_SUCCESS;
}
#endif
#endif

#ifdef GN_PLATFORM_WINDOWS
#include "vulkan/vulkan_win32.h"
GN_EXPORT gnReturnCode gnCreateWindowsWindowSurfaceFn(gnInstance& instance, HWND* window, HINSTANCE* instance) {
    VkWin32SurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    info.hwnd = window;
    info.hinstance = instance;

    VkSurfaceKHR surface;
    VkResult result = vkCreateWin32SurfaceKHR(instance.instance->vk_instance, &info, nullptr, &instance.instance->window_surface);
    if (result != VK_SUCCESS)
        return gnReturnError(GN_FAILED_CREATE_WINDOW_SURFACE, result);
    return GN_SUCCESS;
}
#endif
#include "vulkan/vulkan_metal.h"

#ifdef GN_PLATFORM_MACOS
GN_EXPORT gnReturnCode gnCreateMacOSWindowSurfaceFn(gnInstance& instance, NS::Window* window, NS::View* view) {
    // VkMacOSSurfaceCreateInfoMVK info{};
    // info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    // info.pView = (void*)view;

    VkMetalSurfaceCreateInfoEXT surfaceCreateInfo = {};
    surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
    surfaceCreateInfo.pNext = nullptr;
    surfaceCreateInfo.flags = 0;
    surfaceCreateInfo.pLayer = macosBridge(window, view);

    VkSurfaceKHR surface;
    VkResult result = vkCreateMetalSurfaceEXT(instance.instance->vk_instance, &surfaceCreateInfo, nullptr, &instance.instance->window_surface);
    if (result != VK_SUCCESS)
        return gnReturnError(GN_FAILED_CREATE_WINDOW_SURFACE, result);
    return GN_SUCCESS;
}
#endif
