#include "core/gryphn_handles.h"

#include "core/renderpass/gryphn_render_pass.h"
void gnCommandBeginRenderPass(gnCommandBufferHandle buffer, gnRenderPassInfo passInfo);
void gnCommandEndRenderPass(gnCommandBufferHandle buffer);

#include "core/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
void gnCommandBindGraphicsPipeline(gnCommandBufferHandle buffer, gnGraphicsPipelineHandle graphicsPipeline);
void gnCommandSetViewport(gnCommandBufferHandle buffer, gnViewport viewport);
void gnCommandSetScissor(gnCommandBufferHandle buffer, gnScissor scissor);
void gnCommandBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set);

#include "core/buffers/gryphn_buffer.h"
void gnCommandBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);

void gnCommandDraw(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
void gnCommandDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
