#include "glad/glad.h"
#include "opengl_commands.h"
#include "opengl_command_runner.h"
#include "commands/buffers/opengl_command_buffer.h"
#include "stdio.h"
// #include "framebuffer/opengl_framebuffer.h"

GN_CPP_FUNCTION void openglBeginRenderPass(gnCommandBuffer buffer, gnRenderPassInfo passInfo) {
    openglCommandRunnerBindFunction(buffer->commandBuffer->commmandRunner, []{
        printf("Calling func: %s\n", "Begin Render Pass");
    });

    // glBindFramebuffer(GL_FRAMEBUFFER, passInfo.framebuffer->framebuffer->framebuffers[0]);
    // glClearColor(passInfo.clearValues[0].r, passInfo.clearValues[0].g, passInfo.clearValues[0].b, passInfo.clearValues[0].a);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glEnable(GL_DEPTH_TEST);
    // glViewport(passInfo.offset.x, passInfo.offset.y, passInfo.size.x, passInfo.size.y);
}
GN_CPP_FUNCTION void openglEndRenderPass(gnCommandBuffer buffer) {
    openglCommandRunnerBindFunction(buffer->commandBuffer->commmandRunner, []{
        printf("Calling func: %s\n", "End Render Pass");
    });

    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
GN_CPP_FUNCTION void openglBindGraphicsPipeline(gnCommandBuffer buffer, gnGraphicsPipeline graphicsPipeline);
GN_CPP_FUNCTION void openglSetViewport(gnCommandBuffer buffer, gnViewport viewport);
GN_CPP_FUNCTION void openglSetScissor(gnCommandBuffer buffer, gnScissor scissor);
GN_CPP_FUNCTION void openglBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);
GN_CPP_FUNCTION void openglDraw(gnCommandBuffer buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
GN_CPP_FUNCTION void openglDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
GN_CPP_FUNCTION void openglBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set, uint32_t dynamicOffsetCount, uint32_t* dynamicOffsets);
GN_CPP_FUNCTION void openglBindVertexBytes(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);
