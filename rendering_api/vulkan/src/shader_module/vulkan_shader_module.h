#pragma once
#include <core/shader_module/gryphn_shader_module.h>
#include <vulkan/vulkan.h>

typedef struct gnPlatformShaderModule_t {
    VkShaderModule shaderModule;
    VkPipelineShaderStageCreateInfo shaderStageInfo;
} gnPlatformShaderModule;
