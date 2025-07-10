#pragma once
#include "synchronization/semaphore/gryphn_semaphore.h"
#import <Metal/MTLEvent.h>

typedef struct gnPlatformSemaphore_t {
    id<MTLEvent> event;
    bool eventTriggered;
} gnPlatformSemaphore;

gnReturnCode createMetalSemaphore(gnSemaphore semaphore, gnOutputDevice device);
void destroyMetalSemaphore(gnSemaphore semaphore);
