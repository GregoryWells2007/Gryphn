#include "vulkan_uniform_layout.h"
#include <shader_module/vulkan_shader_module.h>

VkDescriptorType vkGryphnUniformType(gnUniformType type) {
    switch(type) {
    case GN_UNIFORM_BUFFER_DESCRIPTOR: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    case GN_DYNAMIC_UNIFORM_BUFFER_DESCRIPTOR: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    case GN_SHADER_STORE_BUFFER_DESCRIPTOR: return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    case GN_COMBINED_IMAGE_SAMPLER_DESCRIPTOR: return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    case GN_UNIFORM_TYPE_MAX: return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }
}

VkDescriptorSetLayout vkGryphnCreateSetLayouts(
    const gnUniformSet* set,
    VkDevice device
) {
    VkDescriptorSetLayout vkLayout;
    gnUniformSet uniformSet = *set;

    VkDescriptorSetLayoutBinding* bindings = malloc(sizeof(VkDescriptorSetLayoutBinding) * uniformSet.uniformBindingCount);
    for (int i = 0; i < uniformSet.uniformBindingCount; i++) {
        bindings[i] = (VkDescriptorSetLayoutBinding){
            .binding = uniformSet.uniformBindings[i].binding,
            .descriptorCount = 1,
            .descriptorType = vkGryphnUniformType(uniformSet.uniformBindings[i].type),
            .stageFlags = vkGryphnShaderModuleStage(uniformSet.uniformBindings[i].stage)
        };
    }


    VkDescriptorSetLayoutCreateInfo info = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = uniformSet.uniformBindingCount,
        .pBindings = bindings
    };

    if (vkCreateDescriptorSetLayout(device, &info, NULL, &vkLayout) != VK_SUCCESS)
        return NULL;
    return vkLayout;
}
