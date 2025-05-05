#include <vulkan/vulkan.h>
#include <gryphn/gryphn_utils.h>
#include "core/buffers/gryphn_buffer.h"
#include "core/uniform_descriptor/uniform_buffer/gryphn_uniform_buffer.h"
#include "../../output_device/vulkan_output_devices.h"
#include "../vulkan_uniform.h"
#include "../../vertex_buffers/vulkan_buffers.h"

GN_EXPORT void gnUpdateBufferUniformFn(gnBufferUniform& uniformBuffer, const gnOutputDevice& outputDevice) {
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffer.buffer->buffer->buffer;
    bufferInfo.offset = 0;
    bufferInfo.range = uniformBuffer.size;

    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = uniformBuffer.uniform->uniform->descriptorSets[uniformBuffer.index];
    descriptorWrite.dstBinding = uniformBuffer.binding;
    descriptorWrite.dstArrayElement = 0;

    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrite.descriptorCount = 1;

    descriptorWrite.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(outputDevice.outputDevice->device, 1, &descriptorWrite, 0, nullptr);
}


// #include "vulkan/vulkan.h"
// #include "src/uniform_descriptor/uniform_buffer/gryphn_uniform_buffer.h"
// #include "vertex_buffers/vulkan_buffers.h"
// #include "vertex_buffers/buffer_descriptor/vulkan_buffer_description.h"
// #include "output_device/vulkan_output_devices.h"
// #include "uniform_descriptor/vulkan_descriptor_set.h"

// struct gnPlatformUniformBuffer {

// };

// gnUniformBuffer::gnUniformBuffer() {
//     this->uniformBuffer = new gnPlatformUniformBuffer();
// }

// void gnUpdateUniformDescriptor(const gnUniformBuffer& uniformBuffer, const gnOutputDevice& outputDevice) {
//     VkDescriptorBufferInfo bufferInfo{};
//     bufferInfo.buffer = uniformBuffer.buffer->buffer->buffer;
//     bufferInfo.offset = 0;
//     bufferInfo.range = uniformBuffer.size;

//     VkWriteDescriptorSet descriptorWrite{};
//     descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//     descriptorWrite.dstSet = uniformBuffer.descriptorSet->descriptorSet->descriptorSets[uniformBuffer.index];
//     descriptorWrite.dstBinding = uniformBuffer.binding;
//     descriptorWrite.dstArrayElement = 0;

//     descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//     descriptorWrite.descriptorCount = 1;

//     descriptorWrite.pBufferInfo = &bufferInfo;
//     descriptorWrite.pImageInfo = nullptr; // Optional
//     descriptorWrite.pTexelBufferView = nullptr; // Optional

//     vkUpdateDescriptorSets(outputDevice.outputDevice->device, 1, &descriptorWrite, 0, nullptr);
// }
