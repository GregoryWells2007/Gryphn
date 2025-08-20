#pragma once
#include "glad/glad.h"
#include "core/src/uniforms/gryphn_uniform.h"
#include "shaders/opengl_shader_compiler.h"

typedef enum openglUniformType {
    gl_buffer, gl_storage, gl_image
} openglUniformType;

typedef struct glUniformBinding {
    openglUniformType type;
    union {
        gnBufferUniformInfo buffer_info;
        gnStorageUniformInfo storage_info;
        gnImageUniformInfo image_info;
    };
    gnBool isUpdated;
} glUniformBinding;

typedef struct gnPlatformUniform_t {
    glUniformBinding bindings[MAX_OPENGL_BINDINGS];
} gnPlatformUniform;

void openglUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo* info);
void openglUpdateStorageUniform(gnUniform uniform, gnStorageUniformInfo* info);
void openglUpdateImageUniform(gnUniform uniform, gnImageUniformInfo* info);
