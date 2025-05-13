#pragma once
#include "core/instance/gryphn_instance.h"
#include <vulkan/vulkan.h>
#ifdef GN_PLATFORM_MACOS
#include "vulkan_macos_bridge.h"
#endif

struct gnPlatformInstanceData {
    VkInstance vk_instance;
    VkApplicationInfo appInfo;
    VkSurfaceKHR window_surface;

    std::vector<const char*> extensions;
};
