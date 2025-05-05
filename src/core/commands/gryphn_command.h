#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_command_buffer.h"
#include "core/graphics_pipeline/gryphn_render_pass_frame.h"
#include "core/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "core/buffers/gryphn_buffer.h"
#include "core/buffers/uniform_buffer_descriptor/gryphn_buffer_description.h"
#include "core/push_constant/gryphn_push_constant.h"
#include "core/uniform_descriptor/uniform_buffer/gryphn_uniform_buffer.h"
#include "core/uniform_descriptor/sampler/gryphn_sampler.h"
#include "core/shaders/gryphn_shader.h"

struct gnViewportDescriptionData {
    gnVec2 offset;
    gnVec2 size;
    gnVec2 depth;
};

struct gnScissorDescriptionData {
    gnUInt2 offset;
    gnUInt2 extent;
};

inline gnReturnCode (*gnCommandBufferStart)(gnCommandBuffer& commandBuffer);
inline void (*gnCommandBeginRenderPass)(gnCommandBuffer& commandBuffer, const gnRenderPassFrame& frame);
inline void (*gnCommandSetGraphicsPipeline)(gnCommandBuffer& commandBuffer, const gnGraphicsPipeline& graphicsPipeline);
inline void (*gnCommandSetViewport)(gnCommandBuffer& commandBuffer, gnViewportDescriptionData data);
inline void (*gnCommandSetScissor)(gnCommandBuffer& commandBuffer, gnScissorDescriptionData data);
inline void (*_gnCommandDraw)(gnCommandBuffer& commandBuffer, int vertexCount, int instanceCount, int firstVertex, int firstInstance);
inline void gnCommandDraw(gnCommandBuffer& commandBuffer, int vertexCount, int instanceCount, int firstVertex = 0, int firstInstance = 0) { _gnCommandDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance); }
//void gnCommandDrawIndexedIndirect(const gnCommandBuffer &commandBuffer, const gnBuffer& buffer, gnSize offset, gnUInt drawCount, gnUInt stride);
inline void (*gnCommandDrawIndexed)(gnCommandBuffer& commandBuffer, gnUInt indexCount, gnUInt instanceCount, gnUInt firstIndex, gnInt vertexOffset, gnUInt firstInstance);
inline void (*gnCommandEndRenderPass)(gnCommandBuffer& commandBuffer);
inline void (*gnCommandBindBuffer)(gnCommandBuffer& commandBuffer, const gnBuffer& buffer);
inline void (*gnCommandBindBufferUniform)(gnCommandBuffer& commandBuffer, gnGraphicsPipeline& graphicsPipeline, gnBufferUniform& uniformBuffer, gnInt set);
inline void (*gnCommandBindSamplerUniform)(gnCommandBuffer& commandBuffer, const gnGraphicsPipeline& graphicsPipeline, const gnSamplerUniform& sampler, gnInt set);
inline void (*gnCommandPushConstant)(gnCommandBuffer& commandBuffer, const gnGraphicsPipeline& graphicsPipeline, const gnPushConstant& pushConstant, void* data);
inline gnReturnCode (*gnCommandBufferEnd)(gnCommandBuffer& commandBuffer);
