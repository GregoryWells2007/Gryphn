#include "core/command/command_buffer/gryphn_command_buffer.h"


#include "core/renderpass/gryphn_render_pass.h"
void gnCommandBeginRenderPass(struct gnCommandBuffer_t* buffer, struct gnRenderPassInfo_t passInfo);
void gnCommandEndRenderPass(struct gnCommandBuffer_t* buffer);

#include "core/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
void gnCommandBindGraphicsPipeline(struct gnCommandBuffer_t* buffer, struct gnGraphicsPipeline_t* graphicsPipeline);
void gnCommandSetViewport(struct gnCommandBuffer_t* buffer, struct gnViewport_t viewport);
void gnCommandSetScissor(struct gnCommandBuffer_t* buffer, struct gnScissor_t scissor);

void gnCommandDraw(struct gnCommandBuffer_t* buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
