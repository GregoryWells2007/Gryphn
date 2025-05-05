#include "core/shaders/gryphn_shader_module.h"
#include <vulkan/vulkan.h>
#include "vulkan_shader_module.h"
#include "../output_device/vulkan_output_devices.h"

void vulkanShaderModule(gnShaderModule* shaderModule) {
    if (shaderModule->shaderModule == nullptr) shaderModule->shaderModule = new gnPlatformShaderModule();
}

GN_EXPORT gnReturnCode gnBuildShaderModuleFn(gnShaderModule* module, const gnOutputDevice& outputDevice) {
    vulkanShaderModule(module);
    if (module->codeSize < 0 || module->shaderData == nullptr) {
        // TODO: add in error codes so that I can pick up on these errors and not just return that the creation failed
        return GN_FAILED;
    }

    if (module->shaderUse == GN_GRAPHICS_PIPELINE) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = module->codeSize;
        createInfo.pCode = reinterpret_cast<const uint32_t*>(module->shaderData);

        if (vkCreateShaderModule(outputDevice.outputDevice->device, &createInfo, nullptr, &module->shaderModule->module) != VK_SUCCESS) {
            return GN_FAILED;
        }
    }

    module->shaderModule->device = &outputDevice;
    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyShaderModuleFn(gnShaderModule& module) {
    vkDestroyShaderModule(const_cast<gnOutputDevice*>(module.shaderModule->device)->outputDevice->device, module.shaderModule->module, nullptr);
}
