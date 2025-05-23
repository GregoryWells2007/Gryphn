#pragma once
#include <vulkan/vulkan.h>
#include "core/debugger/gryphn_debugger.h"

struct gnInstanceMessage {
    gnMessageSeverity severity;
    gnMessageType type;
    gnMessageData data;
};

typedef struct gnPlatformInstance_t {
    VkInstance vk_instance;
    VkApplicationInfo appInfo;
    // VkSurfaceKHR window_surface;

    // uint16_t extensionCount;
    // const char** extensions;

    uint16_t instanceMessageCount;
    struct gnInstanceMessage* instanceMessages;
} gnPlatformInstance;
