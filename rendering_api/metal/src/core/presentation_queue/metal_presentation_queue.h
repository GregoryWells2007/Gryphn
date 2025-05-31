#pragma once
#import <Metal/Metal.h>
#include "core/presentation_queue/gryphn_presentation_queue.h"

typedef struct gnPlatformPresentationQueue_t {
    int textureCount;
    id<MTLTexture>* textures;

    uint32_t currentImage;
} gnPlatformPresentationQueue;
