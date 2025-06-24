#pragma once
#include "stdint.h"
#include "utils/gryphn_image_format.h"
#include "utils/gryphn_error_code.h"
#include <gryphn_handles.h>

typedef enum gnTextureType {
    GN_TEXTURE_2D
} gnTextureType;

typedef enum gnTextureFilter {
    GN_FILTER_LINEAR, GN_FILTER_NEAREST
} gnTextureFilter;

typedef enum gnTextureWrap {
    GN_REPEAT, GN_MIRRORED_REPEAT, GN_CLAMP_TO_EDGE, GN_CLAMP_TO_BORDER
} gnTextureWrap;

typedef struct gnTextureInfo {
    uint32_t width;
    uint32_t height;
    gnTextureType type;
    gnImageFormat format;
    gnTextureFilter minFilter, magFilter;
    gnTextureWrap wrapU, wrapV, wrapW;
} gnTextureInfo;

#ifdef GN_REVEAL_IMPL
struct gnTexture_t {
    struct gnPlatformTexture_t* texture;
    gnDeviceHandle device;
    gnTextureInfo info;
};
#endif

gnReturnCode gnCreateTexture(gnTexture* texture, gnDevice device, const gnTextureInfo info);
void gnTextureData(gnTextureHandle texture, void* pixelData);
void gnDestroyTexture(gnTexture texture);
