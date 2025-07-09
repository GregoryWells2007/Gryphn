#pragma once
#include "textures/gryphn_texture.h"
#import <Metal/MTLTexture.h>
#import <Metal/MTLSampler.h>

typedef struct gnPlatformTexture_t {
    id<MTLTexture> texture;
    id<MTLSamplerState> sampler;
} gnPlatformTexture;

gnReturnCode createMetalTexture(gnTexture texture, gnDevice device, const gnTextureInfo info);
void metalTextureData(gnTextureHandle texture, void* pixelData);
void metalDestroyTexture(gnTexture texture);


NSUInteger mtlSampleCount(gnMultisampleCountFlags flags);
