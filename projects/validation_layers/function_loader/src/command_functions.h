#include "loader/src/gryphn_command_functions.h"

gnReturnCode checkCommandPoolAllocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool);
gnReturnCode checkBeginCommandBuffer(gnCommandBufferHandle commandBuffer);
void checkResetCommandBuffer(gnCommandBufferHandle commandBuffer);
gnReturnCode checkEndCommandBuffer(gnCommandBufferHandle commandBuffer);
void checkDestroyCommandBuffer(gnCommandBufferHandle commandBuffer);

void checkCommandBeginRenderPass(gnCommandBufferHandle buffer, gnRenderPassInfo passInfo);
void checkCommandEndRenderPass(gnCommandBufferHandle buffer);

void checkCommandBindGraphicsPipeline(gnCommandBufferHandle buffer, gnGraphicsPipelineHandle graphicsPipeline);
void checkCommandSetViewport(gnCommandBufferHandle buffer, gnViewport viewport);
void checkCommandSetScissor(gnCommandBufferHandle buffer, gnScissor scissor);
void checkCommandBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set);
void checkCommandPushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);

void checkCommandBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);
void checkCommandDraw(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
void checkCommandDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
