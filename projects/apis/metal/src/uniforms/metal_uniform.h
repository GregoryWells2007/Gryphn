#pragma once
#include "uniforms/gryphn_uniform.h"
#include <Metal/Metal.h>
#include <uniforms/gryphn_uniform_pool.h>
#include "shader_module/metal_shader_module.h"

typedef struct metalUniformBinding {
    gnUniformType type;
    uint32_t binding;
    void* data;
} metalUniformBinding;

typedef id<MTLResource> mtlResource;

typedef struct gnPlatformUniform_t {
    uint32_t index[MAX_METAL_BINDINGS];
    id<MTLArgumentEncoder> encoder;
    id<MTLBuffer> argumentBuffer;

    mtlResource usedResources[MAX_METAL_BINDINGS];
    int indexMap[MAX_METAL_BINDINGS];
    uint32_t usedResourceCount;
} gnPlatformUniform;

void updateMetalBufferUniform(gnUniform uniform, gnBufferUniformInfo* info);
void updateMetalStorageUniform(gnUniform uniform, gnStorageUniformInfo* info);
void updateMetalImageUniform(gnUniform uniform, gnImageUniformInfo* info);
