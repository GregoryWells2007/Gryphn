#pragma once
#include <shader_module/gryphn_shader_module.h>
#include <vulkan/vulkan.h>

typedef struct gnPlatformShaderModule_t {
    VkShaderModule shaderModule;
    VkPipelineShaderStageCreateInfo shaderStageInfo;
} gnPlatformShaderModule;

VkShaderStageFlagBits vkGryphnShaderModuleStage(gnShaderModuleStage stage);


gnReturnCode createShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo);
void destroyShaderModule(gnShaderModule module);
