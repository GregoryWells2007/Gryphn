#include "vulkan/vulkan.h"
#include "gryphn/gryphn_utils.h"
#include "core/textures/gryphn_texture.h"
#include "core/uniform_descriptor/sampler/gryphn_sampler.h"
#include "../../textures/vulkan_texture.h"
#include "../../output_device/vulkan_output_devices.h"
#include "../vulkan_uniform.h"

GN_EXPORT void gnUpdateSamplerUniformFn(gnSamplerUniform& sampler, const gnOutputDevice& outputDevice) {
    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = sampler.uniform->uniform->descriptorSets[sampler.index];
    descriptorWrite.dstBinding = sampler.binding;
    descriptorWrite.dstArrayElement = 0;

    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWrite.descriptorCount = 1;

    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = sampler.texture->texture->textureImageView;
    imageInfo.sampler = sampler.texture->texture->textureSampler;
    descriptorWrite.pImageInfo = &imageInfo;

    vkUpdateDescriptorSets(outputDevice.outputDevice->device, 1, &descriptorWrite, 0, nullptr);
}
