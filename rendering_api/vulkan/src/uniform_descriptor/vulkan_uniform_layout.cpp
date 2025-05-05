#include "vulkan_uniform_layout.h"
#include "output_device/vulkan_output_devices.h"

GN_EXPORT gnReturnCode gnCreateUniformLayoutFn(gnUniformLayout* uniformLayout, gnOutputDevice& device) {
    uniformLayout->uniformLayout = new gnPlatformUniformLayout();

    uniformLayout->uniformLayout->outputDevice = &device;
    std::vector<VkDescriptorSetLayoutBinding> bindings(uniformLayout->bindings.size());


    for (int i = 0; i < uniformLayout->bindings.size(); i++) {
        bindings[i] = {};
        bindings[i].binding = uniformLayout->bindings[i].binding;
        bindings[i].descriptorType = (uniformLayout->bindings[i].type == GN_UNIFORM_BUFFER_DESCRIPTOR) ? VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER : VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        bindings[i].descriptorCount = 1;

        int stageBit = 0;

        if (gnContainsShaderStage(uniformLayout->bindings[i].stage, GN_VERTEX_SHADER_MODULE)) stageBit |= VK_SHADER_STAGE_VERTEX_BIT;
        if (gnContainsShaderStage(uniformLayout->bindings[i].stage, GN_FRAGMENT_SHADER_MODULE)) stageBit |= VK_SHADER_STAGE_FRAGMENT_BIT;

        bindings[i].stageFlags = stageBit;
        bindings[i].pImmutableSamplers = nullptr;
    }

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = static_cast<uint32_t>(uniformLayout->bindings.size());
    layoutInfo.pBindings = bindings.data();

    if (vkCreateDescriptorSetLayout(device.outputDevice->device, &layoutInfo, nullptr, &uniformLayout->uniformLayout->setLayout) != VK_SUCCESS) {
        return GN_FAILED;
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyUniformLayoutFn(gnUniformLayout& uniformLayout) {
    vkDestroyDescriptorSetLayout(uniformLayout.uniformLayout->outputDevice->outputDevice->device, uniformLayout.uniformLayout->setLayout, nullptr);
}
