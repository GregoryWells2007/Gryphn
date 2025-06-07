#include "vulkan_shader_module.h"
#include "output_device/vulkan_output_devices.h"

VkShaderStageFlagBits vkGryphnShaderModuleStage(gnShaderModuleStage stage) {
    VkShaderStageFlagBits outStage = 0;
    switch(stage) {
    case GN_VERTEX_SHADER_MODULE: outStage |= VK_SHADER_STAGE_VERTEX_BIT; break;
    case GN_FRAGMENT_SHADER_MODULE: outStage |= VK_SHADER_STAGE_FRAGMENT_BIT; break;
    case GN_ALL_SHADER_MODULE: return VK_SHADER_STAGE_ALL_GRAPHICS;
    }
    return outStage;
}

gnReturnCode gnCreateShaderModuleFn(struct gnShaderModule_t *module, struct gnOutputDevice_t *device, struct gnShaderModuleInfo_t shaderModuleInfo) {
    module->shaderModule = malloc(sizeof(struct gnPlatformShaderModule_t));

    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = shaderModuleInfo.size;
    createInfo.pCode = shaderModuleInfo.code;

    if (vkCreateShaderModule(device->outputDevice->device, &createInfo, NULL, &module->shaderModule->shaderModule) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_SHADER_MODULE;
    }

    module->shaderModule->shaderStageInfo = (VkPipelineShaderStageCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = vkGryphnShaderModuleStage(shaderModuleInfo.stage),
        .module = module->shaderModule->shaderModule,
        .pName = shaderModuleInfo.entryPoint.value
    };

    return GN_SUCCESS;
}

void gnDestroyShaderModuleFn(struct gnShaderModule_t* module) {
    vkDestroyShaderModule(module->device->outputDevice->device, module->shaderModule->shaderModule, NULL);
}
