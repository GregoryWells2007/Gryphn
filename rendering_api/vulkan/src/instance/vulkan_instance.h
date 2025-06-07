#pragma once
#include <vulkan/vulkan.h>
#include "core/debugger/gryphn_debugger.h"
#include "core/instance/gryphn_instance.h"

struct gnInstanceMessage {
    gnMessageSeverity severity;
    gnMessageType type;
    gnMessageData data;
};

typedef struct gnPlatformInstance_t {
    VkInstance vk_instance;
    VkApplicationInfo appInfo;

    uint16_t instanceMessageCount;
    struct gnInstanceMessage* instanceMessages;
} gnPlatformInstance;
