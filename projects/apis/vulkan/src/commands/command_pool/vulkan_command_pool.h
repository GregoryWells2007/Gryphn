#pragma once
#include <vulkan/vulkan.h>
#include "command/command_pool/gryphn_command_pool.h"

typedef struct gnPlatformCommandPool_t {
    VkCommandPool commandPool;
} gnPlatformCommandPool;

gnReturnCode createCommandPool(gnCommandPool commandPool, gnDevice device, gnCommandPoolInfo info);
void destroyCommandPool(gnCommandPool commandPool);
