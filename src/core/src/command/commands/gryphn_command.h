#include "gryphn_handles.h"

#include "renderpass/gryphn_render_pass.h"
void gnCommandBeginRenderPass(gnCommandBufferHandle buffer, gnRenderPassInfo passInfo);
void gnCommandEndRenderPass(gnCommandBufferHandle buffer);

#include "pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
void gnCommandBindGraphicsPipeline(gnCommandBufferHandle buffer, gnGraphicsPipelineHandle graphicsPipeline);
void gnCommandSetViewport(gnCommandBufferHandle buffer, gnViewport viewport);
void gnCommandSetScissor(gnCommandBufferHandle buffer, gnScissor scissor);
void gnCommandBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set);
void gnCommandPushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);

#include "buffers/gryphn_buffer.h"
void gnCommandBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);

void gnCommandDraw(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
void gnCommandDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
