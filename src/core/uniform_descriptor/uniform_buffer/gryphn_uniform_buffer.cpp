#include "gryphn_uniform_buffer.h"

void gnBufferUniformBindBuffer(gnBufferUniform& uniformBuffer, const gnBuffer& buffer) { uniformBuffer.buffer = const_cast<gnBuffer*>(&buffer); }
void gnBufferUniformSetSize(gnBufferUniform& uniformBuffer, gnSize size) { uniformBuffer.size = size; }
void gnBufferUniformSetOffset(gnBufferUniform& uniformBuffer, gnSize offset) { uniformBuffer.offset = offset; }
void gnBufferUniformSetBinding(gnBufferUniform& uniformBuffer, gnUInt binding) { uniformBuffer.binding = binding; }
void gnBufferUniformSetUniformIndex(gnBufferUniform& uniformBuffer, gnUInt index) { uniformBuffer.index = index; }
void gnBufferUniformSetUniform(gnBufferUniform& uniformBuffer, const gnUniform& uniform) { uniformBuffer.uniform = const_cast<gnUniform*>(&uniform); }


// void gnUniformBufferBindBuffer(const gnUniformBuffer& uniformBuffer, const gnBuffer& buffer) {
//     const_cast<gnUniformBuffer*>(&uniformBuffer)->buffer = const_cast<gnBuffer*>(&buffer);
// }
// void gnUniformBufferSetSize(const gnUniformBuffer& uniformBuffer, gnSize size) {
//     const_cast<gnUniformBuffer*>(&uniformBuffer)->size = size;
// }
// void gnUniformBufferSetOffset(const gnUniformBuffer& uniformBuffer, gnSize offset) {
//     const_cast<gnUniformBuffer*>(&uniformBuffer)->offset = offset;
// }

// void gnUniformBufferSetBinding(const gnUniformBuffer& uniformBuffer, gnUInt binding) {
//     const_cast<gnUniformBuffer*>(&uniformBuffer)->binding = binding;
// }
// void gnUniformBufferSetDescriptorIndex(const gnUniformBuffer& uniformBuffer, gnUInt index) {
//     const_cast<gnUniformBuffer*>(&uniformBuffer)->index = index;
// }
// void gnUniformBufferSetDescriptorSet(const gnUniformBuffer& uniformBuffer, const gnDescriptorSet& descriptorSet) {
//     const_cast<gnUniformBuffer*>(&uniformBuffer)->descriptorSet = const_cast<gnDescriptorSet*>(&descriptorSet);
// }


// /// I HAVE NO FUCKING CLUE WHAT THIS GOD DAMN FUNCITON EVER DID AND IF IT WILL EVER DO ANYTHING AGAIN
// void gnUniformBufferSetDescriptor(const gnUniformBuffer& uniformBuffer, const gnBufferDescription& bufferDescription) {
//     //const_cast<gnUniformBuffer*>(&uniformBuffer)->bufferDescription = const_cast<gnBufferDescription*>(&bufferDescription);
// }
