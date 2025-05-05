#pragma once
#include <gryphn/gryphn_utils.h>
#include <core/shaders/gryphn_shader.h>

struct gnPlatformUniformLayoutBinding;

typedef int gnUniformLayoutBindingType;
#define GN_UNIFORM_BUFFER_DESCRIPTOR 0
#define GN_SAMPLER_DESCRIPTOR 1

struct gnUniformLayoutBinding {
ACCESS_LEVEL:
    gnPlatformUniformLayoutBinding* uniformLayoutBinding;

    gnUInt binding = 0;
    gnShaderModuleStage stage = GN_VERTEX_SHADER_MODULE;
    gnUniformLayoutBindingType type = GN_UNIFORM_BUFFER_DESCRIPTOR;
public:
    gnUniformLayoutBinding() {}
};

void gnUniformLayoutBindingSetBinding(gnUniformLayoutBinding& uniformLayoutBinding, gnUInt binding);
void gnUniformLayoutBindingSetShaderStage(gnUniformLayoutBinding& uniformLayoutBinding, gnShaderModuleStage stage);
void gnUniformLayoutBindingSetType(gnUniformLayoutBinding& uniformLayoutBinding, gnUniformLayoutBindingType type);
