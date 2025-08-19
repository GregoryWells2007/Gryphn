#include "glad/glad.h"
#include "opengl_commands.h"
#include "framebuffer/opengl_framebuffer.h"

void openglBeginRenderPass(gnCommandBuffer buffer, gnRenderPassInfo passInfo) {
    glBindFramebuffer(GL_FRAMEBUFFER, passInfo.framebuffer->framebuffer->framebuffers[0]);
    glClearColor(passInfo.clearValues[0].r, passInfo.clearValues[0].g, passInfo.clearValues[0].b, passInfo.clearValues[0].a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glViewport(passInfo.offset.x, passInfo.offset.y, passInfo.size.x, passInfo.size.y);
}
void openglEndRenderPass(gnCommandBuffer buffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void openglBindGraphicsPipeline(gnCommandBuffer buffer, gnGraphicsPipeline graphicsPipeline);
void openglSetViewport(gnCommandBuffer buffer, gnViewport viewport);
void openglSetScissor(gnCommandBuffer buffer, gnScissor scissor);
void openglBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);
void openglDraw(gnCommandBuffer buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
void openglDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
void openglBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set, uint32_t dynamicOffsetCount, uint32_t* dynamicOffsets);
void openglBindVertexBytes(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);
