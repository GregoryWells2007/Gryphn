#pragma once
#include "uniforms/gryphn_uniform.h"
#include <uniforms/gryphn_uniform_pool.h>

typedef struct metalUniformBinding {
    gnUniformType type;
    uint32_t binding;
    void* data;
} metalUniformBinding;

typedef struct gnPlatformUniform_t {
    uint32_t bindingCount;
    metalUniformBinding* bindings;
} gnPlatformUniform;

void updateMetalBufferUniform(gnUniform uniform, gnBufferUniformInfo* info);
void updateMetalImageUniform(gnUniform uniform, gnImageUniformInfo* info);
