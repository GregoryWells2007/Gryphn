#include <vulkan/vulkan.h>
#include "core/shaders/gryphn_shader.h"
#include "vulkan_shader_module.h"

VkShaderStageFlagBits vulkanShaderModuleType(gnShaderModuleStage name) {
    if (name == GN_VERTEX_SHADER_MODULE) return VK_SHADER_STAGE_VERTEX_BIT;
    if (name == GN_FRAGMENT_SHADER_MODULE) return VK_SHADER_STAGE_FRAGMENT_BIT;
    return VK_SHADER_STAGE_VERTEX_BIT; // assume that shits a vertex shader
}

GN_EXPORT gnReturnCode gnBuildShaderFn(gnShader* shader) {
    for (int i = 0; i < gnListLength(shader->shaderModules); i++) {
        gnShaderModule* module = gnListGetPtr(shader->shaderModules, i);
        // std::cout << "Building ";
        // if (module->shaderType == GN_VERTEX_SHADER_MODULE) std::cout << "GN_VERTEX_SHADER_MODULE";
        // if (module->shaderType == GN_FRAGMENT_SHADER_MODULE) std::cout << "GN_FRAGMENT_SHADER_MODULE";
        // std::cout << " shader\n";


        module->shaderModule->stageCreateInfo = {};
        module->shaderModule->stageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        module->shaderModule->stageCreateInfo.stage = vulkanShaderModuleType(module->shaderType);
        module->shaderModule->stageCreateInfo.module = module->shaderModule->module;
        module->shaderModule->stageCreateInfo.pName = "main";
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnShaderDestroyModulesFn(gnShader& shader) {
    for (int i = 0; i < gnListLength(shader.shaderModules); i++) {
        gnShaderModule* module = gnListGetPtr(shader.shaderModules, i);
        gnDestroyShaderModule(*module);
    }
}
