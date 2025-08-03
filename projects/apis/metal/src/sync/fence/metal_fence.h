#pragma once
#include "synchronization/fence/gryphn_fence.h"
#import <Metal/Metal.h>
#import <Metal/MTLEvent.h>

typedef struct gnPlatformFence_t {
    uint32_t currentValue;
    id<MTLSharedEvent> event;
} gnPlatformFence;

gnReturnCode createMetalFence(gnFence fence, gnDevice device);
void waitForMetalFence(gnFence fence, uint64_t timeout);
void resetMetalFence(gnFence fence);
void destroyMetalFence(gnFence fence);
