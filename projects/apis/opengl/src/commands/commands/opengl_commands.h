#pragma once
#include "core/src/command/commands/gryphn_command.h"
#include "utils/gryphn_cpp_function.h"

GN_CPP_FUNCTION void openglBeginRenderPass(gnCommandBuffer buffer, gnRenderPassInfo passInfo);
GN_CPP_FUNCTION void openglEndRenderPass(gnCommandBuffer buffer);
GN_CPP_FUNCTION void openglBindGraphicsPipeline(gnCommandBuffer buffer, gnGraphicsPipeline graphicsPipeline);
GN_CPP_FUNCTION void openglSetViewport(gnCommandBuffer buffer, gnViewport viewport);
GN_CPP_FUNCTION void openglSetScissor(gnCommandBuffer buffer, gnScissor scissor);
GN_CPP_FUNCTION void openglBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);
GN_CPP_FUNCTION void openglDraw(gnCommandBuffer buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
GN_CPP_FUNCTION void openglDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
GN_CPP_FUNCTION void openglBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set, uint32_t dynamicOffsetCount, uint32_t* dynamicOffsets);
GN_CPP_FUNCTION void openglPushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);
