#pragma once
#include <vulkan/vulkan.h>
#include "debugger/gryphn_debugger.h"
#include "instance/gryphn_instance.h"

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
