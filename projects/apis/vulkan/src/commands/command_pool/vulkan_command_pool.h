#pragma once
#include <vulkan/vulkan.h>
#include "command/command_pool/gryphn_command_pool.h"

typedef struct gnPlatformCommandPool_t {
    VkCommandPool commandPool;
} gnPlatformCommandPool;
