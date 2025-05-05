#pragma once
#include <gryphn/gryphn_utils.h>
#include "../gryphn_uniform.h"
#include "core/textures/gryphn_texture.h"

struct gnPlatformSamplerUniform;

struct gnSamplerUniform {
ACCESS_LEVEL:
    gnPlatformSamplerUniform* samplerUniform = nullptr;
    const gnTexture* texture;
    gnUInt binding = 0;
    gnUInt index = 0;
    gnUniform* uniform;
public:
    gnSamplerUniform() {}
};

void gnSamplerUniformSetTexture(gnSamplerUniform& samplerUniform, const gnTexture& texture);
void gnSamplerUniformSetTexture(gnSamplerUniform& samplerUniform, const gnTexture* texture);
void gnSamplerUniformSetBinding(gnSamplerUniform& samplerUniform, gnUInt binding);
void gnSamplerUniformSetUniformIndex(gnSamplerUniform& samplerUniform, gnUInt index);
void gnSamplerUniformSetUniform(gnSamplerUniform& samplerUniform, const gnUniform& uniformDescriptor);

inline void (*gnUpdateSamplerUniform)(gnSamplerUniform& samplerUniform, const gnOutputDevice& outputDevice);
