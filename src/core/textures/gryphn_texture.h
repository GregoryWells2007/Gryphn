#pragma once
#include "stdint.h"
#include "stdlib.h"
#include "utils/gryphn_image_format.h"
#include "utils/gryphn_error_code.h"
#include <core/gryphn_handles.h>

typedef enum gnTextureType {
    GN_TEXTURE_2D
} gnTextureType;

typedef struct gnTextureInfo {
    uint32_t width;
    uint32_t height;
    gnTextureType type;
    gnImageFormat format;
} gnTextureInfo;

#ifdef GN_REVEAL_IMPL
struct gnTexture_t {
    struct gnPlatformTexture_t* texture;
    gnDeviceHandle device;
};
#endif

gnReturnCode gnCreateTexture(gnTexture* texture, gnDevice device, const gnTextureInfo info);
