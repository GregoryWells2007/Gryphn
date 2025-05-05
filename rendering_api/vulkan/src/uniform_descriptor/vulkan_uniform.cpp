#include "vulkan_uniform.h"
#include "output_device/vulkan_output_devices.h"
#include "vulkan_uniform_layout.h"

void gnUniformSetCount(gnUniform& uniform, gnUInt count) {
    uniform.descriptorCount = count;
}
void gnUniformSetLayout(gnUniform& uniform, gnUniformLayout* uniformLayout) {
    uniform.uniformLayout = uniformLayout;
}
GN_EXPORT gnReturnCode gnCreateUniformFn(gnUniform* uniform, gnOutputDevice& outputDevice) {
    uniform->uniform = new gnPlatformUniform();
    uniform->uniform->outputDevice = &outputDevice;

    std::vector<VkDescriptorPoolSize> poolSizes;
    poolSizes.resize(uniform->uniformLayout->bindings.size());


    for (int i = 0; i < uniform->uniformLayout->bindings.size(); i++) {
        poolSizes[i].type = (uniform->uniformLayout->bindings[i].type == GN_UNIFORM_BUFFER_DESCRIPTOR) ? VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER : VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[i].descriptorCount = static_cast<uint32_t>(uniform->descriptorCount);
    }

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(uniform->descriptorCount);

    if (vkCreateDescriptorPool(outputDevice.outputDevice->device, &poolInfo, nullptr, &uniform->uniform->descriptorPool) != VK_SUCCESS) {
        return GN_FAILED;
    }

    std::vector<VkDescriptorSetLayout> layouts(uniform->descriptorCount, uniform->uniformLayout->uniformLayout->setLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = uniform->uniform->descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(uniform->descriptorCount);
    allocInfo.pSetLayouts = layouts.data();

    uniform->uniform->descriptorSets.resize(uniform->descriptorCount);

    if (vkAllocateDescriptorSets(outputDevice.outputDevice->device, &allocInfo, &uniform->uniform->descriptorSets[0]) != VK_SUCCESS) {
        return GN_FAILED;
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyUniformFn(gnUniform& uniform) {
    vkDestroyDescriptorPool(uniform.uniform->outputDevice->outputDevice->device, uniform.uniform->descriptorPool, nullptr);
}
