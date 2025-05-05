#pragma once
#include <Metal/Metal.hpp>

struct gnPlatformSyncSemaphore {
    // MTL::Fence* semaphore;
    dispatch_semaphore_t semaphore;
};
