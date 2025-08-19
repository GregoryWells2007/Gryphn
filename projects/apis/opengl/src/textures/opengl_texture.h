#pragma once
#include <glad/glad.h>
#include "textures/gryphn_texture.h"

typedef struct gnPlatformTexture_t {
    GLuint id;
} gnPlatformTexture;

gnReturnCode openglCreateTexture(gnTexture texture, gnDevice device, const gnTextureInfo info);
void openglTextureData(gnTextureHandle texture, void* pixelData);
void openglDestroyTexture(gnTexture texture);
