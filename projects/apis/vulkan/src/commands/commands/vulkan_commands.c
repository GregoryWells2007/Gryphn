#include "vulkan_commands.h"
#include "stdio.h"

void beginRenderPass(gnCommandBuffer buffer, gnRenderPassInfo passInfo) {

    VkClearValue* values = malloc(sizeof(VkClearValue) * passInfo.clearValueCount);
    for (uint32_t i = 0; i < passInfo.clearValueCount; i++) {
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
void endRenderPass(gnCommandBuffer buffer) {
    vkCmdEndRenderPass(buffer->commandBuffer->buffer);
}
void bindGraphicsPipeline(gnCommandBuffer buffer, gnGraphicsPipeline graphicsPipeline) {
    buffer->commandBuffer->boundGraphicsPipeline = graphicsPipeline;
    vkCmdBindPipeline(buffer->commandBuffer->buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline->graphicsPipeline->graphicsPipeline);
}
void setViewport(gnCommandBuffer buffer, gnViewport viewport) {
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
void setScissor(gnCommandBuffer buffer, gnScissor scissor) {
    VkRect2D vkScissor = {
        .extent = { scissor.size.x, scissor.size.y },
        .offset = { scissor.position.x, scissor.position.y }
    };
    vkCmdSetScissor(buffer->commandBuffer->buffer, 0, 1, &vkScissor);
}
VkDeviceSize offsets[] = {0};
void bindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type)  {
    if (type == GN_VERTEX_BUFFER)
        vkCmdBindVertexBuffers(buffer->commandBuffer->buffer, 0, 1, &bufferToBind->buffer->buffer.buffer, offsets);
    else if (type == GN_INDEX_BUFFER) {
        buffer->commandBuffer->changedBuffer = GN_TRUE;
        buffer->commandBuffer->boundIndexBuffer = bufferToBind;
    }
}
void draw(gnCommandBuffer buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance) {
    vkCmdDraw(buffer->commandBuffer->buffer, vertexCount, instanceCount, firstVertex, firstInstance);
}
void drawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance)  {
    if (buffer->commandBuffer->changedBuffer) vkCmdBindIndexBuffer(buffer->commandBuffer->buffer, buffer->commandBuffer->boundIndexBuffer->buffer->buffer.buffer, 0, (type == GN_UINT32) ? VK_INDEX_TYPE_UINT32 : VK_INDEX_TYPE_UINT16);
    vkCmdDrawIndexed(buffer->commandBuffer->buffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    buffer->commandBuffer->changedBuffer = GN_FALSE;
}

void bindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set, uint32_t dynamicOffsetCount, uint32_t* dynamicOffsets) {
    vkCmdBindDescriptorSets(
        buffer->commandBuffer->buffer,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->pipelineLayout, set, 1,
        &uniform->uniform->set, dynamicOffsetCount, dynamicOffsets
    );
}

void pushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data) {
    vkCmdPushConstants(
        buffer->commandBuffer->buffer,
        buffer->commandBuffer->boundGraphicsPipeline->graphicsPipeline->pipelineLayout,
        vkGryphnShaderModuleStage(layout.stage),
        layout.offset,
        layout.size,
        data
    );
}
