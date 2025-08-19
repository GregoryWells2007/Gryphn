#pragma once
#include "core/src/command/commands/gryphn_command.h"

void openglBeginRenderPass(gnCommandBuffer buffer, gnRenderPassInfo passInfo);
void openglEndRenderPass(gnCommandBuffer buffer);
void openglBindGraphicsPipeline(gnCommandBuffer buffer, gnGraphicsPipeline graphicsPipeline);
void openglSetViewport(gnCommandBuffer buffer, gnViewport viewport);
void openglSetScissor(gnCommandBuffer buffer, gnScissor scissor);
void openglBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);
void openglDraw(gnCommandBuffer buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
void openglDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
void openglBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set, uint32_t dynamicOffsetCount, uint32_t* dynamicOffsets);
void openglBindVertexBytes(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);
