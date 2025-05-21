#pragma once
#include <vulkan/vulkan.h>
#ifdef GN_PLATFORM_MACOS
#include <instance/vulkan_macos_bridge.h>
#endif
#include "vector"
#include "core/debugger/gryphn_debugger.h"

struct gnInstanceMessage {
    gnMessageSeverity severity;
    gnMessageType type;
    gnMessageData data;
};

struct gnPlatformInstance {
    VkInstance vk_instance;
    VkApplicationInfo appInfo;
    VkSurfaceKHR window_surface;

    std::vector<const char*> extensions;
    std::vector<gnInstanceMessage> instanceMessages;
};
