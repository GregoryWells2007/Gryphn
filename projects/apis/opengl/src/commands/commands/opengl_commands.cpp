#include "glad/glad.h"
#include "opengl_commands.h"
#include "opengl_command_runner.h"
#include "commands/buffers/opengl_command_buffer.h"
#include "framebuffer/opengl_framebuffer.h"
#include <string.h>
#include "buffer/opengl_buffer.h"
#include "graphics_pipeline/opengl_graphics_pipeline.h"
#include "renderpass/opengl_render_pass_descriptor.h"
#include "uniforms/uniform/opengl_uniform.h"
#include "textures/opengl_texture.h"

GN_CPP_FUNCTION void openglBeginRenderPass(gnCommandBuffer buffer, gnRenderPassInfo sPassInfo) {
    gnRenderPassInfo passInfo = sPassInfo;
    gnClearValue* values = (gnClearValue*)malloc(sizeof(gnClearValue*) * passInfo.clearValueCount);
    memcpy(values, passInfo.clearValues, sizeof(gnClearValue*) * passInfo.clearValueCount);

    openglCommandRunnerBindFunction(buffer->commandBuffer->commmandRunner, std::function<void()>([passInfo, values]{
        glBindFramebuffer(GL_FRAMEBUFFER, passInfo.framebuffer->framebuffer->framebuffers[0]);
        if (passInfo.renderPassDescriptor->renderPassDescriptor->subpasses[0].colorAttachments[0].format == GL_SRGB8_ALPHA8) glEnable(GL_FRAMEBUFFER_SRGB);
        glClearColor(values[0].r, values[0].g, values[0].b, values[0].a);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(passInfo.offset.x, passInfo.offset.y, passInfo.size.x, passInfo.size.y);
        free(values);
    }));
}
GN_CPP_FUNCTION void openglEndRenderPass(gnCommandBuffer buffer) {
    openglCommandRunnerBindFunction(buffer->commandBuffer->commmandRunner, std::function<void()>([]{
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_FRAMEBUFFER_SRGB);
    }));
}
GN_CPP_FUNCTION void openglBindGraphicsPipeline(gnCommandBuffer commandBuffer, gnGraphicsPipeline graphicsPipeline) {
    gnGraphicsPipeline pipeline = graphicsPipeline;
    gnCommandBuffer buffer = commandBuffer;
    openglCommandRunnerBindFunction(buffer->commandBuffer->commmandRunner, std::function<void()>([buffer, pipeline]{
        buffer->commandBuffer->boundGraphicsPipeline = pipeline;
        glBindVertexArray(buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->vertexArrayObject);

        if (buffer->commandBuffer->boundVertexBuffer != GN_NULL_HANDLE)
            glVertexArrayVertexBuffer(
                buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->vertexArrayObject, 0,
                buffer->commandBuffer->boundVertexBuffer->buffer->id, 0,
                buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->stride
            );
        if (buffer->commandBuffer->boundIndexBuffer != GN_NULL_HANDLE)
            glVertexArrayElementBuffer(buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->vertexArrayObject, buffer->commandBuffer->boundIndexBuffer->buffer->id);

        glUseProgram(buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->program);
    }));
}
GN_CPP_FUNCTION void openglSetViewport(gnCommandBuffer buffer, gnViewport viewport) {

}
GN_CPP_FUNCTION void openglSetScissor(gnCommandBuffer buffer, gnScissor scissor) {

}
GN_CPP_FUNCTION void openglBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type) {
    gnBufferType bType = type;
    gnCommandBufferHandle bBuffer = buffer;
    gnBufferHandle bBufferToBind = bufferToBind;

    openglCommandRunnerBindFunction(buffer->commandBuffer->commmandRunner, std::function<void()>([bType, bBuffer, bBufferToBind]{
        if (bType == GN_VERTEX_BUFFER) {
            bBuffer->commandBuffer->boundVertexBuffer = bBufferToBind;
            glVertexArrayVertexBuffer(
                bBuffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->vertexArrayObject, 0,
                bBuffer->commandBuffer->boundVertexBuffer->buffer->id, 0,
                bBuffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->stride
            );
        } else if (bType == GN_INDEX_BUFFER) {
            bBuffer->commandBuffer->boundIndexBuffer = bBufferToBind;
            glVertexArrayElementBuffer(bBuffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->vertexArrayObject, bBufferToBind->buffer->id);
        }
    }));
}
GN_CPP_FUNCTION void openglDraw(gnCommandBuffer buffer, int sVertexCount, int sFirstVertex, int sInstanceCount, int sFirstInstance) {
    int vertexCount = sVertexCount, firstVertex = sFirstVertex, instanceCount = sInstanceCount, firstInstance = sFirstInstance;
    openglCommandRunnerBindFunction(buffer->commandBuffer->commmandRunner, std::function<void()>([vertexCount, firstVertex, instanceCount, firstInstance]{
        glDrawArraysInstancedBaseInstance(GL_TRIANGLES, firstVertex, vertexCount, instanceCount, firstInstance);
    }));
}
GN_CPP_FUNCTION void openglDrawIndexed(gnCommandBufferHandle sBuffer, gnIndexType sType, int sIndexCount, int sFirstIndex, int sVertexOffset, int sInstanceCount, int sFirstInstance) {
    gnCommandBuffer buffer = sBuffer;
    gnIndexType type = sType;
    int indexCount = sIndexCount, firstIndex = sFirstIndex, vertexOffset = sVertexOffset, instanceCount = sInstanceCount, firstInstance = sFirstInstance;
    openglCommandRunnerBindFunction(buffer->commandBuffer->commmandRunner, std::function<void()>([buffer, type, indexCount, firstIndex, instanceCount, vertexOffset, firstInstance]{
        glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, indexCount, (type == GN_UINT16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * firstIndex), instanceCount, vertexOffset, firstInstance);
    }));
}
#include "stdio.h"
GN_CPP_FUNCTION void openglBindUniform(gnCommandBufferHandle sBuffer, gnUniform sUniform, uint32_t sSet, uint32_t dynamicOffsetCount, uint32_t* dynamicOffsets) {
    gnCommandBufferHandle buffer = sBuffer;
    gnUniform uniform = sUniform;
    uint32_t set = sSet;

    openglCommandRunnerBindFunction(buffer->commandBuffer->commmandRunner, std::function<void()>([buffer, uniform, set]{
        for (int i = 0; i < MAX_OPENGL_BINDINGS; i++) {
            if (uniform->uniform->bindings[i].isUpdated != GN_TRUE) continue;
            if (uniform->uniform->bindings[i].type == gl_image) {
                glActiveTexture(GL_TEXTURE0 + buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->setMap[set].bindings[uniform->uniform->bindings[i].image_info.binding]);
                glBindTexture(GL_TEXTURE_2D, uniform->uniform->bindings[i].image_info.texture->texture->id);
            } else if (uniform->uniform->bindings[i].type == gl_buffer) {
                glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniform->uniform->bindings[i].buffer_info.buffer->buffer->id);
                glUniformBlockBinding(
                    buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->program,
                    buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->setMap[set].bindings[uniform->uniform->bindings[i].buffer_info.binding],
                    0
                );
            } else if (uniform->uniform->bindings[i].type == gl_storage) {
                // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, uniform->uniform->bindings[i].storage_info.buffer->buffer->id);
                // glFlushMappedNamedBufferRange(uniform->uniform->bindings[i].buffer_info.buffer->buffer->id, 0, uniform->uniform->bindings[i].buffer_info.buffer->info.size);
            }
        }
    }));
}
GN_CPP_FUNCTION void openglPushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data) {

}
