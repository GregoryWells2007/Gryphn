#pragma once
#include "sync/semaphore/gryphn_semaphore.h"
#import <Metal/MTLEvent.h>

typedef struct gnPlatformSemaphore_t {
    id<MTLEvent> event;
    bool eventTriggered;
} gnPlatformSemaphore;
