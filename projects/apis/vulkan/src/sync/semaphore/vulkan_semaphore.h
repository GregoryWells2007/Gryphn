#pragma once
#include <vulkan/vulkan.h>
#include "synchronization/semaphore/gryphn_semaphore.h"

typedef struct gnPlatformSemaphore_t {
    VkSemaphore semaphore;
} gnPlatformSemaphore;

gnReturnCode createSemaphore(gnSemaphore semaphore, gnDevice device);
void destroySemaphore(gnSemaphore semaphore);
