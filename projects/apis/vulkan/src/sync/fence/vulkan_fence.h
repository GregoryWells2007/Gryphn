#pragma once
#include <vulkan/vulkan.h>
#include "core/sync/fence/gryphn_fence.h"

typedef struct gnPlatformFence_t {
    VkFence fence;
} gnPlatformFence;
