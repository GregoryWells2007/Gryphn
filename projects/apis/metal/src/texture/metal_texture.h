#pragma once
#include "textures/gryphn_texture.h"
#import <Metal/MTLTexture.h>

typedef struct gnPlatformTexture_t {
    id<MTLTexture> texture;
} gnPlatformTexture;
