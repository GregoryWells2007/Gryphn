#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/output_device/gryphn_output_device.h"

enum gnTextureType {
    GN_TEXTURE_2D = 0, GN_TEXTURE_CUBE_MAP = 1
};

enum gnTextureFilter {
    GN_FILTER_LINEAR = 0, GN_FILTER_NEAREST = 1
};

struct gnPlatformTexture;

static int currentTextureID = 0;

struct gnTexture {
ACCESS_LEVEL:
    gnPlatformTexture* texture = nullptr;
    gnTextureType textureType;
    gnColorMode textureColorFormat;
    gnUInt2 textureExtent;

    gnTextureFilter minFilter = GN_FILTER_LINEAR;
    gnTextureFilter magFilter = GN_FILTER_LINEAR;

    gnUInt dataSize;

    gnUInt TextureID;
public:
    gnTexture() {
        // I should handle this somewhere else but im not going to
        TextureID = currentTextureID;
        currentTextureID++;
    }
};
void gnTextureSetType(gnTexture& texture, gnTextureType type);
void gnTextureSetFormat(gnTexture& texture, gnColorMode format);
void gnTextureSetExtent(gnTexture& texture, gnUInt2 extent);
inline void gnTextureSetSize(gnTexture& texture, gnUInt2 size) { gnTextureSetExtent(texture, size); }
void gnTextureSetMinFilter(gnTexture& texture, gnTextureFilter filter);
void gnTextureSetMagFilter(gnTexture& texture, gnTextureFilter filter);
gnUInt gnGetTextureID(gnTexture& texture);

inline void (*gnTextureData)(gnTexture& texture, gnSize dataSize, const void* data);
inline void (*gnTextureCubeMapData)(gnTexture& texture, gnSize imageDataSize, void* face1, void* face2, void* face3, void* face4, void* face5, void* face6);
inline gnErrorCode (*gnCreateTexture)(gnTexture* texture, const gnOutputDevice& outputDevice);
inline void (*gnDestroyTexture)(gnTexture& texture);
