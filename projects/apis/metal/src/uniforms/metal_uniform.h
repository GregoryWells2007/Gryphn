#pragma once
#include "uniforms/gryphn_uniform.h"
#include <Metal/Metal.h>
#include <uniforms/gryphn_uniform_pool.h>
#include "shader_module/metal_shader_module.h"

typedef struct metalUniformBinding {
    gnUniformType type;
    uint32_t binding;
    void* data;

    gnBool isDynamic;
} metalUniformBinding;

typedef id<MTLResource> mtlResource;

typedef struct gnPlatformUniform_t {
    uint32_t index[MAX_METAL_BINDINGS];
    gnShaderModuleStage stageUsed[MAX_METAL_BINDINGS];
    id<MTLArgumentEncoder> encoders[mtlMaxStage];
    id<MTLBuffer> argumentBuffers[mtlMaxStage];
    mtlResource usedResources[MAX_METAL_BINDINGS];
    int indexMap[MAX_METAL_BINDINGS];
    uint32_t usedResourceCount;

    gnBool isDynamic[MAX_METAL_BINDINGS];
} gnPlatformUniform;

void updateMetalBufferUniform(gnUniform uniform, gnBufferUniformInfo* info);
void updateMetalStorageUniform(gnUniform uniform, gnStorageUniformInfo* info);
void updateMetalImageUniform(gnUniform uniform, gnImageUniformInfo* info);


typedef struct mtlBufferUniformInfo {
    gnBufferUniformInfo* baseInfo;
    id<MTLBuffer> buffer;
} mtlBufferUniformInfo;

void mtlUpdateMetalBufferUniform(gnUniformHandle uniform, mtlBufferUniformInfo* info);
