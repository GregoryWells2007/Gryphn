#include "gryphn_command.h"
#include "core/gryphn_platform_functions.h"

void gnCommandBeginRenderPass(struct gnCommandBuffer_t* buffer, struct gnRenderPassInfo_t passInfo) {
    buffer->commandPool->commandFunctions->_gnCommandBeginRenderPass(buffer, passInfo);
}
void gnCommandEndRenderPass(struct gnCommandBuffer_t* buffer) {
    buffer->commandPool->commandFunctions->_gnCommandEndRenderPass(buffer);
}

void gnCommandBindGraphicsPipeline(struct gnCommandBuffer_t* buffer, struct gnGraphicsPipeline_t* graphicsPipeline) {
    buffer->commandPool->commandFunctions->_gnCommandBindGraphicsPipeline(buffer, graphicsPipeline);
}
void gnCommandSetViewport(struct gnCommandBuffer_t* buffer, struct gnViewport_t viewport) {
    buffer->commandPool->commandFunctions->_gnCommandSetViewport(buffer, viewport);
}
void gnCommandSetScissor(struct gnCommandBuffer_t* buffer, struct gnScissor_t scissor) {
    buffer->commandPool->commandFunctions->_gnCommandSetScissor(buffer, scissor);
}
void gnCommandBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set) {
    buffer->commandPool->commandFunctions->_gnCommandBindUniform(buffer, uniform, set);
}
void gnCommandBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type) {
    buffer->commandPool->commandFunctions->_gnCommandBindBuffer(buffer, bufferToBind, type);
}
void gnCommandDraw(struct gnCommandBuffer_t* buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance) {
    buffer->commandPool->commandFunctions->_gnCommandDraw(buffer, vertexCount, firstVertex, instanceCount, firstInstance);
}
void gnCommandDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance) {
    buffer->commandPool->commandFunctions->_gnCommandDrawIndexed(buffer, type, indexCount, firstIndex, vertexOffset, instanceCount, firstInstance);
}
