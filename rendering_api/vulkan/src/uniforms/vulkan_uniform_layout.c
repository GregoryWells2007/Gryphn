#include "vulkan_uniform_layout.h"
#include <shader_module/vulkan_shader_module.h>

VkDescriptorType vkGryphnUniformType(gnUniformType type) {
    switch(type) {
    case GN_UNIFORM_BUFFER_DESCRIPTOR: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    case GN_UNIFORM_TYPE_MAX: return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }
}

VkDescriptorSetLayout* vkGryphnCreateSetLayouts(
    const gnUniformLayout* layout, uint32_t* setCount,
    VkDevice device
) {
    gnUniformLayout uniformLayout = *layout;

    *setCount = uniformLayout.uniformBindingCount;
    VkDescriptorSetLayout* sets = malloc(sizeof(VkDescriptorSetLayoutBinding) * uniformLayout.uniformBindingCount);
    for (int i = 0; i < uniformLayout.uniformBindingCount; i++) {
        VkDescriptorSetLayoutBinding setLayout = {
            .binding = uniformLayout.uniformBindings[i].binding,
            .descriptorCount = 1,
            .descriptorType = vkGryphnUniformType(uniformLayout.uniformBindings[i].type),
            .stageFlags = vkGryphnShaderModuleStage(uniformLayout.uniformBindings[i].stage)
        };

        VkDescriptorSetLayoutCreateInfo info = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .bindingCount = 1,
            .pBindings = &setLayout
        };

        if (vkCreateDescriptorSetLayout(device, &info, NULL, sets) != VK_SUCCESS) {
            return NULL;
        }
    }
    return sets;
}
