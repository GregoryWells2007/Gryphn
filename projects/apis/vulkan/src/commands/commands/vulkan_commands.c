#include <vulkan/vulkan.h>
#include "command/commands/gryphn_command.h"
#include <renderpass/vulkan_render_pass_descriptor.h>
#include "framebuffers/vulkan_framebuffer.h"
#include "commands/command_buffer/vulkan_command_buffer.h"
#include "pipelines/graphics_pipeline/vulkan_graphics_pipeline.h"
#include "buffers/vulkan_buffer.h"
#include "uniforms/vulkan_uniform.h"
#include "shader_module/vulkan_shader_module.h"

void gnCommandBeginRenderPassFn(gnCommandBuffer buffer, struct gnRenderPassInfo_t passInfo) {
    VkClearValue* values = malloc(sizeof(VkClearValue) * passInfo.clearValueCount);
    for (int i = 0; i < passInfo.clearValueCount; i++) {
        values[i] = (VkClearValue){{{
            passInfo.clearValues[i].red,
            passInfo.clearValues[i].green,
            passInfo.clearValues[i].blue,
            passInfo.clearValues[i].alpha
        }}};
    }

    VkRenderPassBeginInfo renderPassInfo ={
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = passInfo.renderPassDescriptor->renderPassDescriptor->renderPass,
        .framebuffer = passInfo.framebuffer->framebuffer->framebuffer,
        .renderArea = {
            .extent = { passInfo.size.x, passInfo.size.y },
            .offset = { passInfo.offset.x, passInfo.offset.y }
        },
        .clearValueCount = passInfo.clearValueCount,
        .pClearValues = values,
    };

    vkCmdBeginRenderPass(buffer->commandBuffer->buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}
void gnCommandEndRenderPassFn(gnCommandBuffer buffer) {
    vkCmdEndRenderPass(buffer->commandBuffer->buffer);
}
void gnCommandBindGraphicsPipelineFn(gnCommandBuffer buffer, gnGraphicsPipeline graphicsPipeline) {
    buffer->commandBuffer->boundGraphicsPipeline = graphicsPipeline;
    vkCmdBindPipeline(buffer->commandBuffer->buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline->graphicsPipeline->graphicsPipeline);
}
void gnCommandSetViewportFn(gnCommandBuffer buffer, gnViewport viewport) {
    VkViewport vkViewport = {
        .x = viewport.position.x,
        .y = viewport.size.y,
        .width = viewport.size.x,
        .height = -viewport.size.y,
        .minDepth = viewport.minDepth,
        .maxDepth = viewport.maxDepth
    };
    vkCmdSetViewport(buffer->commandBuffer->buffer, 0, 1, &vkViewport);
}
void gnCommandSetScissorFn(gnCommandBuffer buffer, struct gnScissor_t scissor) {
    VkRect2D vkScissor = {
        .extent = { scissor.size.x, scissor.size.y },
        .offset = { scissor.position.x, scissor.position.y }
    };
    vkCmdSetScissor(buffer->commandBuffer->buffer, 0, 1, &vkScissor);
}
VkDeviceSize offsets[] = {0};
void gnCommandBindBufferFn(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type)  {
    if (type == GN_VERTEX_BUFFER)
        vkCmdBindVertexBuffers(buffer->commandBuffer->buffer, 0, 1, &bufferToBind->buffer->buffer.buffer, offsets);
    else if (type == GN_INDEX_BUFFER) {
        buffer->commandBuffer->changedBuffer = gnTrue;
        buffer->commandBuffer->boundIndexBuffer = bufferToBind;
    }
}
void gnCommandDrawFn(gnCommandBuffer buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance) {
    vkCmdDraw(buffer->commandBuffer->buffer, vertexCount, instanceCount, firstVertex, firstInstance);
}
void gnCommandDrawIndexedFn(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance)  {
    if (buffer->commandBuffer->changedBuffer) vkCmdBindIndexBuffer(buffer->commandBuffer->buffer, buffer->commandBuffer->boundIndexBuffer->buffer->buffer.buffer, 0, (type == GN_UINT32) ? VK_INDEX_TYPE_UINT32 : VK_INDEX_TYPE_UINT16);
    vkCmdDrawIndexed(buffer->commandBuffer->buffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    buffer->commandBuffer->changedBuffer = gnFalse;
}

void gnCommandBindUniformFn(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set) {
    vkCmdBindDescriptorSets(
        buffer->commandBuffer->buffer,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->pipelineLayout, set, 1,
        &uniform->uniform->set, 0, NULL
    );
}

void gnCommandPushConstantFn(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data) {
    vkCmdPushConstants(
        buffer->commandBuffer->buffer,
        buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->pipelineLayout,
        vkGryphnShaderModuleStage(layout.stage),
        layout.offset,
        layout.size,
        data
    );
}
