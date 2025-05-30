#pragma once
#include "core/sync/fence/gryphn_fence.h"
#import <Metal/Metal.h>
#import <Metal/MTLEvent.h>

typedef struct gnPlatformFence_t {
    id<MTLSharedEvent> fence;
    MTLSharedEventListener* listener;
    dispatch_semaphore_t semaphore;
} gnPlatformFence;
