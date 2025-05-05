#pragma once
#include <core/shaders/gryphn_shader_module.h>
#include <Metal/Metal.hpp>

struct gnPlatformShaderModule {
    MTL::Function* shaderFunction;
    int uniformBufferOffset = 0, pushConstantOffset = 0;
    std::unordered_map<gnUInt2, gnUInt> texturesSetBindings;
};
