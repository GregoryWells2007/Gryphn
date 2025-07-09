#pragma once
#include <vulkan/vulkan.h>
#include "synchronization/fence/gryphn_fence.h"

typedef struct gnPlatformFence_t {
    VkFence fence;
} gnPlatformFence;

gnReturnCode createFence(gnFence fence, gnDevice device);
void waitForFence(gnFence fence, uint64_t timeout);
void resetFence(gnFence fence);
void destroyFence(gnFence fence);
