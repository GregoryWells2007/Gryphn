#include "gryphn/gryphn_utils.h"
#include "core/commands/gryphn_command.h"
#include "vulkan_command_buffer.h"
#include "../graphics_pipeline/vulkan_renderpass.h"
#include "../graphics_pipeline/vulkan_graphics_pipeline.h"
#include "../vertex_buffers/vulkan_buffers.h"
#include "../push_constant/vulkan_push_constant.h"
#include "core/shaders/gryphn_shader_module.h"
#include "core/uniform_descriptor/uniform_buffer/gryphn_uniform_buffer.h"
#include "../uniform_descriptor/vulkan_uniform.h"
#include <vulkan/vulkan_core.h>
#include "../framebuffers/vulkan_framebuffer.h"
#include <array>

GN_EXPORT gnReturnCode gnCommandBufferStartFn(const gnCommandBuffer& commandBuffer) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0; // Optional
    beginInfo.pInheritanceInfo = nullptr; // Optional

    if (vkBeginCommandBuffer(commandBuffer.commandBuffer->commandBuffer, &beginInfo) != VK_SUCCESS) {
        return GN_FAILED;
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnCommandBeginRenderPassFn(gnCommandBuffer& commandBuffer, const gnRenderPassFrame& frame) {
    gnRenderPassFrame* frameptr = const_cast<gnRenderPassFrame*>(&frame);
    if (frame.renderPassFrame == nullptr) frameptr->renderPassFrame = new gnPlatformRenderPassFrame();
    frameptr->renderPassFrame->renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    frameptr->renderPassFrame->renderPassInfo.renderPass = frameptr->renderPass->renderpass->renderPass;
    frameptr->renderPassFrame->renderPassInfo.framebuffer = frameptr->framebuffer->framebuffer->framebuffer;
    frameptr->renderPassFrame->renderPassInfo.renderArea.offset = { (int)frameptr->offset.x, (int)frameptr->offset.y };
    frameptr->renderPassFrame->renderPassInfo.renderArea.extent = { frameptr->area.x, frameptr->area.y };

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {{frame.clearColor.r / 255.0f, frame.clearColor.g / 255.0f, frame.clearColor.b / 255.0f, frame.clearColor.a}};
    clearValues[1].depthStencil = {1.0f, 0};
    frame.renderPassFrame->renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    frame.renderPassFrame->renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffer.commandBuffer->commandBuffer, &frame.renderPassFrame->renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

GN_EXPORT void gnCommandSetGraphicsPipelineFn(const gnCommandBuffer& commandBuffer, const gnGraphicsPipeline& graphicsPipeline) {
    vkCmdBindPipeline(commandBuffer.commandBuffer->commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.graphicsPipeline->graphicsPipeline);
}

GN_EXPORT void gnCommandSetViewportFn(const gnCommandBuffer& commandBuffer, gnViewportDescriptionData data) {
    commandBuffer.commandBuffer->viewport.x = data.offset.x;
    commandBuffer.commandBuffer->viewport.y = data.offset.y;
    commandBuffer.commandBuffer->viewport.width = data.size.x;
    commandBuffer.commandBuffer->viewport.height = data.size.y;
    commandBuffer.commandBuffer->viewport.minDepth = data.depth.a;
    commandBuffer.commandBuffer->viewport.maxDepth = data.depth.b;

    vkCmdSetViewport(commandBuffer.commandBuffer->commandBuffer, 0, 1, &commandBuffer.commandBuffer->viewport);
}
GN_EXPORT void gnCommandSetScissorFn(const gnCommandBuffer& commandBuffer, gnScissorDescriptionData data) {
    commandBuffer.commandBuffer->scissor.offset = {(int)data.offset.x, (int)data.offset.y};
    commandBuffer.commandBuffer->scissor.extent = { data.extent.x, data.extent.y };
    vkCmdSetScissor(commandBuffer.commandBuffer->commandBuffer, 0, 1, &commandBuffer.commandBuffer->scissor);
}
GN_EXPORT void gnCommandBindBufferFn(const gnCommandBuffer& commandBuffer, const gnBuffer& buffer) {
    if (buffer.bufferType == GN_VERTEX_BUFFER) {
        VkBuffer vertexBuffers[] = {buffer.buffer->buffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer.commandBuffer->commandBuffer, 0, 1, vertexBuffers, offsets);
    } else {
        VkIndexType type;
        if (buffer.dataType == GN_UINT8) { /* TODO: switch to vulkan 1.4 */ }
        if (buffer.dataType == GN_UINT16) { type = VK_INDEX_TYPE_UINT16; /* TODO: switch to vulkan 1.4 */ }
        if (buffer.dataType == GN_UINT32) { type = VK_INDEX_TYPE_UINT32; /* TODO: switch to vulkan 1.4 */ }

        vkCmdBindIndexBuffer(commandBuffer.commandBuffer->commandBuffer, buffer.buffer->buffer, 0, type);
    }
}

GN_EXPORT void gnCommandDrawFn(const gnCommandBuffer& commandBuffer, int vertexCount, int instanceCount, int firstVertex, int firstInstance) {
    vkCmdDraw(commandBuffer.commandBuffer->commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}
GN_EXPORT void gnCommandDrawIndexedFn(const gnCommandBuffer& commandBuffer, gnUInt indexCount, gnUInt instanceCount, gnUInt firstIndex, gnInt vertexOffset, gnUInt firstInstance) {
    vkCmdDrawIndexed(commandBuffer.commandBuffer->commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}
GN_EXPORT void gnCommandBindBufferUniformFn(const gnCommandBuffer& commandBuffer, gnGraphicsPipeline& graphicsPipeline, gnBufferUniform& uniformBuffer, gnInt set) {
    vkCmdBindDescriptorSets(
        commandBuffer.commandBuffer->commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
        graphicsPipeline.graphicsPipeline->pipelineLayout, set, 1,
        &uniformBuffer.uniform->uniform->descriptorSets[uniformBuffer.index], 0, nullptr
    );
}
GN_EXPORT void gnCommandBindSamplerUniformFn(const gnCommandBuffer& commandBuffer, const gnGraphicsPipeline& graphicsPipeline, const gnSamplerUniform& sampler, gnInt set) {
    vkCmdBindDescriptorSets(
        commandBuffer.commandBuffer->commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
        graphicsPipeline.graphicsPipeline->pipelineLayout, set, 1,
        &sampler.uniform->uniform->descriptorSets[sampler.index], 0, nullptr
    );
}
GN_EXPORT void gnCommandPushConstantFn(gnCommandBuffer& commandBuffer, const gnGraphicsPipeline& graphicsPipeline, const gnPushConstant& pushConstant, void* data) {
    int stageBit = 0;

    if (gnContainsShaderStage(pushConstant.stage, GN_VERTEX_SHADER_MODULE)) stageBit |= VK_SHADER_STAGE_VERTEX_BIT;
    if (gnContainsShaderStage(pushConstant.stage, GN_FRAGMENT_SHADER_MODULE)) stageBit |= VK_SHADER_STAGE_FRAGMENT_BIT;

    vkCmdPushConstants(commandBuffer.commandBuffer->commandBuffer,
        graphicsPipeline.graphicsPipeline->pipelineLayout,
        stageBit, pushConstant.offset, pushConstant.size, data);
}
GN_EXPORT void gnCommandEndRenderPassFn(const gnCommandBuffer& commandBuffer) {
    vkCmdEndRenderPass(commandBuffer.commandBuffer->commandBuffer);
}
void gnCommandBindShader(const gnCommandBuffer& commandBuffer, const gnShader& shader) {
    // vkCmdBindShadersEXT(
    //     commandBuffer.commandBuffer->commandBuffer,
    //     2,
    //     VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
    //     const VkShaderEXT*                          pShaders);
}
GN_EXPORT gnReturnCode gnCommandBufferEndFn(const gnCommandBuffer& commandBuffer) {
    if (vkEndCommandBuffer(commandBuffer.commandBuffer->commandBuffer) != VK_SUCCESS) {
        return GN_FAILED;
    }
    return GN_SUCCESS;
}
