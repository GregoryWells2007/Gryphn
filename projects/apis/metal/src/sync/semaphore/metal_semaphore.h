#pragma once
#include "synchronization/semaphore/gryphn_semaphore.h"
#import <Metal/MTLEvent.h>
#import <Metal/MTLCommandBuffer.h>
#import <stdatomic.h>

typedef struct gnPlatformSemaphore_t {
    id<MTLEvent> event;
    atomic_uint_fast64_t currentValue;
} gnPlatformSemaphore;

gnReturnCode createMetalSemaphore(gnSemaphore semaphore, gnOutputDevice device);
void destroyMetalSemaphore(gnSemaphore semaphore);


void mtlSignalSemaphore(gnSemaphore semaphore, id<MTLCommandBuffer> cmdBuf);
void mtlWaitSemaphore(gnSemaphore semaphore, id<MTLCommandBuffer> cmdBuf);
