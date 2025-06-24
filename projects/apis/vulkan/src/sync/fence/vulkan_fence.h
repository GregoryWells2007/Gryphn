#pragma once
#include <vulkan/vulkan.h>
#include "sync/fence/gryphn_fence.h"

typedef struct gnPlatformFence_t {
    VkFence fence;
} gnPlatformFence;
