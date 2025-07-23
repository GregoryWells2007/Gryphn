#pragma once
#import <Metal/Metal.h>
#include "presentation_queue/gryphn_presentation_queue.h"

typedef id<MTLTexture> metalTexture;
GN_ARRAY_LIST(metalTexture);

typedef struct mtlImageNeeded {
    gnSemaphore semaphoreToSignal;
    uint32_t* whereToPut;
} mtlImageNeeded;
GN_ARRAY_LIST(mtlImageNeeded);

typedef struct gnPlatformPresentationQueue_t {
    metalTextureArrayList textures;
    uint32_tArrayList avaliableTextures;

    mtlImageNeededArrayList neededImages;

    gnVec2 createdSize;
    // gnVec2 createdWindowSize;
} gnPlatformPresentationQueue;

gnReturnCode createMetalPresentationQueue(gnPresentationQueueHandle presentationQueue, const gnDevice device, gnPresentationQueueInfo presentationInfo);
gnReturnCode getMetalPresentQueueImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphore semaphore, uint32_t* imageIndex);
gnReturnCode getMetalPresentQueueImage(gnPresentationQueueHandle presentationQueue, uint32_t* imageIndex);
void destroyMetalPresentationQueue(gnPresentationQueueHandle presentationQueue);

void mtlAddImageBackToQueue(gnPresentationQueue queue, uint32_t index);
