#pragma once
#include "stdint.h"
#include "shader_module/gryphn_shader_module.h"

typedef enum gnUniformType {
    GN_UNIFORM_BUFFER_DESCRIPTOR,
    GN_DYNAMIC_UNIFORM_BUFFER_DESCRIPTOR,
    GN_SHADER_STORE_BUFFER_DESCRIPTOR,
    GN_COMBINED_IMAGE_SAMPLER_DESCRIPTOR,
    GN_UNIFORM_TYPE_MAX
} gnUniformType;

typedef struct gnUniformBinding {
    uint32_t binding;
    gnUniformType type;
    gnShaderModuleStage stage;
} gnUniformBinding;

typedef struct gnUniformSet {
    uint32_t uniformBindingCount;
    gnUniformBinding* uniformBindings;
} gnUniformSet;

typedef struct gnPushConstantLayout {
    gnShaderModuleStage  stage;
    size_t size;
    size_t offset;
} gnPushConstantLayout;

typedef struct gnUniformLayout {
    uint32_t setCount;
    gnUniformSet* sets;
    uint32_t pushConstantCount;
    gnPushConstantLayout* pushConstants;
} gnUniformLayout;
