#include "command/commands/gryphn_command.h"
#include "framebuffers/metal_framebuffer.h"
#include "commands/command_buffer/metal_command_buffer.h"
#include "pipelines/graphics_pipeline/metal_graphics_pipeline.h"
#include "buffer/metal_buffer.h"
#include "uniforms/metal_uniform.h"
#include "texture/metal_texture.h"
#import <Metal/MTLRenderCommandEncoder.h>

void metelBeginRenderPass(gnCommandBuffer buffer, gnRenderPassInfo passInfo);
void endMetalRenderPass(gnCommandBuffer buffer);
void bindMetalGraphicsPipeline(gnCommandBuffer buffer, struct gnGraphicsPipeline_t* graphicsPipeline);
void setMetalViewport(gnCommandBuffer buffer, gnViewport viewport);
void setMetalScissor(gnCommandBuffer buffer, gnScissor scissor);
void bindMetalBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);
void metalDraw(gnCommandBuffer buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
void metalDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
void metalBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set, uint32_t dynamicOffsetCount, uint32_t* dynamicOffsets);
void metalBindVertexBytes(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);
