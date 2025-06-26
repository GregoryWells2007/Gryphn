#include "gryphn_command.h"
#include "command/command_buffer/gryphn_command_buffer.h"
#include "command/command_pool/gryphn_command_pool.h"
#include "instance/gryphn_instance.h"

void gnCommandBeginRenderPass(gnCommandBufferHandle buffer, gnRenderPassInfo passInfo) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandBeginRenderPass(buffer, passInfo);
}
void gnCommandEndRenderPass(gnCommandBufferHandle buffer) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandEndRenderPass(buffer);
}

void gnCommandBindGraphicsPipeline(gnCommandBufferHandle buffer, gnGraphicsPipeline graphicsPipeline) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandBindGraphicsPipeline(buffer, graphicsPipeline);
}
void gnCommandSetViewport(gnCommandBufferHandle buffer, gnViewport viewport) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandSetViewport(buffer, viewport);
}
void gnCommandSetScissor(gnCommandBufferHandle buffer, gnScissor scissor) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandSetScissor(buffer, scissor);
}
void gnCommandBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandBindUniform(buffer, uniform, set);
}
void gnCommandBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandBindBuffer(buffer, bufferToBind, type);
}
void gnCommandPushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandPushConstant(buffer, layout, data);
}
void gnCommandDraw(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandDraw(buffer, vertexCount, firstVertex, instanceCount, firstInstance);
}
void gnCommandDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance) {
    buffer->commandPool->instance->callingLayer->commandFunctions._gnCommandDrawIndexed(buffer, type, indexCount, firstIndex, vertexOffset, instanceCount, firstInstance);
}
