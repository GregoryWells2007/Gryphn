#pragma once
#include "core/instance/gryphn_instance.h"
#include <vulkan/vulkan.h>

struct gnPlatformInstanceData {
    VkInstance vk_instance;
    VkApplicationInfo appInfo;
    VkSurfaceKHR window_surface;
    GLFWwindow* window;
};
