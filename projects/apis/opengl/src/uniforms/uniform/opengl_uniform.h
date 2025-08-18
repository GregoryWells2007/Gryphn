#pragma once
#include "glad/glad.h"
#include "core/src/uniforms/gryphn_uniform.h"

typedef enum openglUniformType {
    gl_buffer, gl_storage, gl_image
} openglUniformType;

typedef struct gnPlatformUniform_t {
    openglUniformType type;
    union {
        gnBufferUniformInfo buffer_info;
        gnStorageUniformInfo storage_info;
        gnImageUniformInfo image_info;
    };
} gnPlatformUniform;

void openglUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo* info);
void openglUpdateStorageUniform(gnUniform uniform, gnStorageUniformInfo* info);
void openglUpdateImageUniform(gnUniform uniform, gnImageUniformInfo* info);
