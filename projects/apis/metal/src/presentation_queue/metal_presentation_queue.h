#pragma once
#import <Metal/Metal.h>
#include "presentation_queue/gryphn_presentation_queue.h"

typedef struct gnPlatformPresentationQueue_t {
    int textureCount;
    id<MTLTexture>* textures;

    uint32_t currentImage;
} gnPlatformPresentationQueue;

gnReturnCode createMetalPresentationQueue(gnPresentationQueueHandle presentationQueue, const gnDevice device, gnPresentationQueueInfo presentationInfo);
gnReturnCode getMetalPresentQueueImage(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphore semaphore, uint32_t* imageIndex);
void destroyMetalPresentationQueue(gnPresentationQueueHandle presentationQueue);
