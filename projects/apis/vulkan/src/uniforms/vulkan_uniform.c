#include "vulkan_uniform.h"
#include "buffers/vulkan_buffer.h"
#include "output_device/vulkan_output_devices.h"
#include "uniforms/gryphn_uniform_pool.h"
#include "textures/vulkan_texture.h"

void gnUpdateBufferUniformFn(gnUniform uniform, gnBufferUniformInfo* info) {
    VkDescriptorBufferInfo bufferInfo = {
        .buffer = info->buffer->buffer->buffer.buffer,
        .offset = info->offset,
        .range = info->size
    };

    VkWriteDescriptorSet write = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1,
        .pBufferInfo = &bufferInfo,
        .dstSet = uniform->uniform->set,
        .dstBinding = info->binding,
        .dstArrayElement = 0
    };

    vkUpdateDescriptorSets(uniform->pool->device->outputDevice->device, 1, &write, 0, NULL);
}

void gnUpdateImageUniformFn(gnUniform uniform, gnImageUniformInfo* info) {
    VkDescriptorImageInfo imageInfo = {
        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        .imageView = info->texture->texture->image.imageView,
        .sampler = info->texture->texture->sampler
    };

    VkWriteDescriptorSet write = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .descriptorCount = 1,
        .pImageInfo = &imageInfo,
        .dstSet = uniform->uniform->set,
        .dstBinding = info->binding,
        .dstArrayElement = 0
    };

    vkUpdateDescriptorSets(uniform->pool->device->outputDevice->device, 1, &write, 0, NULL);
}
