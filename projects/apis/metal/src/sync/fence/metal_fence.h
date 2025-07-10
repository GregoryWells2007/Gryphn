#pragma once
#include "synchronization/fence/gryphn_fence.h"
#import <Metal/Metal.h>
#import <Metal/MTLEvent.h>

typedef struct gnPlatformFence_t {} gnPlatformFence;

gnReturnCode createMetalFence(gnFence fence, gnDevice device);
void singalMetalFence(gnFence fence);
void waitForMetalFence(gnFence fence, uint64_t timeout);
void resetMetalFence(gnFence fence);
void destroyMetalFence(gnFence fence);
