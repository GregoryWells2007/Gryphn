#pragma once
#include "core/sync/semaphore/gryphn_semaphore.h"
#import <Metal/MTLEvent.h>

typedef struct gnPlatformSemaphore_t {
    id<MTLEvent> event;
} gnPlatformSemaphore;
