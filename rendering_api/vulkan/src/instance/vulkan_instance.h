#pragma once
#include "core/instance/gryphn_instance.h"
#include <vulkan/vulkan.h>
#ifdef GN_PLATFORM_MACOS
#include "vulkan_macos_bridge.h"
#endif
#include "vector"

struct gnPlatformInstance {
    VkInstance vk_instance;
    VkApplicationInfo appInfo;
    VkSurfaceKHR window_surface;

    std::vector<const char*> extensions;
};
