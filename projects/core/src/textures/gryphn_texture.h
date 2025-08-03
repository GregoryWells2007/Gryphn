#pragma once
#include "core/gryphn_image_format.h"
#include "core/gryphn_return_code.h"
#include "utils/math/gryphn_vec3.h"
#include "core/src/output_device/gryphn_physical_output_device.h"
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

typedef enum gnTextureUsageFlags {
    GN_TEXTURE_USAGE_COLOR_ATTACHMENT         = 1 << 0,
    GN_TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT = 1 << 1,
    GN_TEXTURE_RESOLVE_ATTACHMENT             = 1 << 2,
    GN_TEXTURE_USAGE_SAMPLED                  = 1 << 3,
    GN_TEXTURE_USAGE_WRITE_TARGET             = 1 << 4,
} gnTextureUsageFlags;

typedef struct gnTextureInfo {
    gnExtent3D extent;
    gnMultisampleCountFlags samples;
    gnTextureUsageFlags usage;
    uint32_t mipmapLevels;
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
