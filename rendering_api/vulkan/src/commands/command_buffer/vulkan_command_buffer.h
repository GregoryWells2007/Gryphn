#pragma once
#include "core/command/command_buffer/gryphn_command_buffer.h"
#include "utils/gryphn_bool.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformCommandBuffer_t {
    VkCommandBuffer buffer;

    gnBool changedBuffer;
    gnBufferHandle boundIndexBuffer;
} gnPlatformCommandBuffer;
