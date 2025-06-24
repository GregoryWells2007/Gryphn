#pragma once
#include <vulkan/vulkan.h>
#include "sync/semaphore/gryphn_semaphore.h"

typedef struct gnPlatformSemaphore_t {
    VkSemaphore semaphore;
} gnPlatformSemaphore;
