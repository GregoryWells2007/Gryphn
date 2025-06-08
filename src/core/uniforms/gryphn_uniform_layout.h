#pragma once
#include "stdint.h"
#include "core/shader_module/gryphn_shader_module.h"

typedef enum gnUniformType {
    GN_UNIFORM_BUFFER_DESCRIPTOR
} gnUniformType;

typedef struct gnUniformBinding {
    uint32_t binding;
    gnUniformType type;
    gnShaderModuleStage stage;
} gnUniformBinding;

typedef struct gnUniformLayout {
    uint32_t uniformBindingCount;
    gnUniformBinding* uniformBindings;
} gnUniformLayout;
