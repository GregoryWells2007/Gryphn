#pragma once
#include <vulkan/vulkan.h>
#include "command/commands/gryphn_command.h"
#include <renderpass/vulkan_render_pass_descriptor.h>
#include <framebuffers/vulkan_framebuffer.h>
#include <commands/command_buffer/vulkan_command_buffer.h>
#include <pipelines/graphics_pipeline/vulkan_graphics_pipeline.h>
#include <buffers/vulkan_buffer.h>
#include <uniforms/vulkan_uniform.h>
#include <shader_module/vulkan_shader_module.h>

void beginRenderPass(gnCommandBuffer buffer, gnRenderPassInfo passInfo);
void endRenderPass(gnCommandBuffer buffer);
void bindGraphicsPipeline(gnCommandBuffer buffer, gnGraphicsPipeline graphicsPipeline);
void setViewport(gnCommandBuffer buffer, gnViewport viewport);
void setScissor(gnCommandBuffer buffer, gnScissor scissor);
void bindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);
void draw(gnCommandBuffer buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
void drawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
void bindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set);
void pushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);
