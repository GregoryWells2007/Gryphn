#pragma once
#include <shader_module/gryphn_shader_module.h>
#include <vulkan/vulkan.h>

typedef struct gnPlatformShaderModule_t {
    VkShaderModule shaderModule;
    VkPipelineShaderStageCreateInfo shaderStageInfo;
} gnPlatformShaderModule;

VkShaderStageFlagBits vkGryphnShaderModuleStage(gnShaderModuleStage stage);
