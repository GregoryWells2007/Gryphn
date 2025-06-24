#include "gryphn_command.h"
#include "command/command_buffer/gryphn_command_buffer.h"
#include "command/command_pool/gryphn_command_pool.h"

void gnCommandBeginRenderPass(gnCommandBufferHandle buffer, gnRenderPassInfo passInfo) {
    buffer->commandPool->commandFunctions->_gnCommandBeginRenderPass(buffer, passInfo);
}
void gnCommandEndRenderPass(gnCommandBufferHandle buffer) {
    buffer->commandPool->commandFunctions->_gnCommandEndRenderPass(buffer);
}

void gnCommandBindGraphicsPipeline(gnCommandBufferHandle buffer, gnGraphicsPipeline graphicsPipeline) {
    buffer->commandPool->commandFunctions->_gnCommandBindGraphicsPipeline(buffer, graphicsPipeline);
}
void gnCommandSetViewport(gnCommandBufferHandle buffer, gnViewport viewport) {
    buffer->commandPool->commandFunctions->_gnCommandSetViewport(buffer, viewport);
}
void gnCommandSetScissor(gnCommandBufferHandle buffer, gnScissor scissor) {
    buffer->commandPool->commandFunctions->_gnCommandSetScissor(buffer, scissor);
}
void gnCommandBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set) {
    buffer->commandPool->commandFunctions->_gnCommandBindUniform(buffer, uniform, set);
}
void gnCommandBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type) {
    buffer->commandPool->commandFunctions->_gnCommandBindBuffer(buffer, bufferToBind, type);
}
void gnCommandPushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data) {
    buffer->commandPool->commandFunctions->_gnCommandPushConstant(buffer, layout, data);
}
void gnCommandDraw(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance) {
    buffer->commandPool->commandFunctions->_gnCommandDraw(buffer, vertexCount, firstVertex, instanceCount, firstInstance);
}
void gnCommandDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance) {
    buffer->commandPool->commandFunctions->_gnCommandDrawIndexed(buffer, type, indexCount, firstIndex, vertexOffset, instanceCount, firstInstance);
}
