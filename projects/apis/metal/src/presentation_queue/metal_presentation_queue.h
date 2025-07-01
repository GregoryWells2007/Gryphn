#pragma once
#import <Metal/Metal.h>
#include "presentation_queue/gryphn_presentation_queue.h"

typedef id<MTLTexture> metalTexture;
GN_ARRAY_LIST(metalTexture);

typedef struct gnPlatformPresentationQueue_t {
    metalTextureArrayList textures;
    uint32_tArrayList avaliableTextures;
} gnPlatformPresentationQueue;

gnReturnCode createMetalPresentationQueue(gnPresentationQueueHandle presentationQueue, const gnDevice device, gnPresentationQueueInfo presentationInfo);
gnReturnCode getMetalPresentQueueImage(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphore semaphore, uint32_t* imageIndex);
void destroyMetalPresentationQueue(gnPresentationQueueHandle presentationQueue);
