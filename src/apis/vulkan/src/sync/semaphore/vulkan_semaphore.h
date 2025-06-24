#pragma once
#include <vulkan/vulkan.h>
#include "core/sync/semaphore/gryphn_semaphore.h"

typedef struct gnPlatformSemaphore_t {
    VkSemaphore semaphore;
} gnPlatformSemaphore;
