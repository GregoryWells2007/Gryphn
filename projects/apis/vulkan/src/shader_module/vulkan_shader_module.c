#include "vulkan_shader_module.h"
#include "output_device/vulkan_output_devices.h"
#include "vulkan_result_converter.h"

VkShaderStageFlagBits vkGryphnShaderModuleStage(gnShaderModuleStage stage) {
    VkShaderStageFlagBits outStage = 0;
    if ((stage & GN_VERTEX_SHADER_MODULE) == GN_VERTEX_SHADER_MODULE) outStage |= VK_SHADER_STAGE_VERTEX_BIT;
    if ((stage & GN_FRAGMENT_SHADER_MODULE) == GN_FRAGMENT_SHADER_MODULE) outStage |= VK_SHADER_STAGE_FRAGMENT_BIT;
    if ((stage & GN_ALL_SHADER_MODULE) == GN_ALL_SHADER_MODULE) return VK_SHADER_STAGE_ALL_GRAPHICS;
    return outStage;
}

gnReturnCode createShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo) {
    module->shaderModule = malloc(sizeof(struct gnPlatformShaderModule_t));
    VkShaderModuleCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = shaderModuleInfo.size,
        .pCode = shaderModuleInfo.code
    };
    VkResult result = vkCreateShaderModule(device->outputDevice->device, &createInfo, NULL, &module->shaderModule->shaderModule);
    if (result == VK_SUCCESS) {
        module->shaderModule->shaderStageInfo = (VkPipelineShaderStageCreateInfo){
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = vkGryphnShaderModuleStage(shaderModuleInfo.stage),
            .module = module->shaderModule->shaderModule,
            .pName = gnToCString(shaderModuleInfo.entryPoint)
        };
    }

    return VkResultToGnReturnCode(result);
}

void destroyShaderModule(gnShaderModule module) {
    vkDestroyShaderModule(module->device->outputDevice->device, module->shaderModule->shaderModule, NULL);
}
