#include "command_functions.h"
#include "core/src/command/command_pool/gryphn_command_pool.h"
#include "core/src/command/command_buffer/gryphn_command_buffer.h"
#include "core/src/output_device/gryphn_output_device.h"
#include <core/src/instance/gryphn_debugger.h>
#include <core/src/instance/gryphn_instance.h>
#include "core/src/renderpass/gryphn_render_pass.h"
#include "core/src/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "core/src/buffers/gryphn_buffer.h"
#include "loader_utils.h"

gnReturnCode checkCommandPoolAllocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool) {
    CHECK_FUNCTION_WITH_RETURN_CODE(pool->device->instance, _gnCommandPoolAllocateCommandBuffers, commandFunctions, commandBuffers, count, pool);
}
gnReturnCode checkBeginCommandBuffer(gnCommandBufferHandle commandBuffer) {
    CHECK_FUNCTION_WITH_RETURN_CODE(commandBuffer->instance, _gnBeginCommandBuffer, commandFunctions, commandBuffer);
}
void checkResetCommandBuffer(gnCommandBufferHandle commandBuffer) {
    CHECK_VOID_FUNCTION(commandBuffer->instance, _gnResetCommandBuffer, commandFunctions, commandBuffer);
}
gnReturnCode checkEndCommandBuffer(gnCommandBufferHandle commandBuffer) {
    CHECK_FUNCTION_WITH_RETURN_CODE(commandBuffer->instance, _gnEndCommandBuffer, commandFunctions, commandBuffer);
}
void checkDestroyCommandBuffer(gnCommandBufferHandle buffer) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnDestroyCommandBuffer, commandFunctions, buffer);
}

void checkCommandBeginRenderPass(gnCommandBufferHandle buffer, gnRenderPassInfo passInfo) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandBeginRenderPass, commandFunctions, buffer, passInfo);
}
void checkCommandEndRenderPass(gnCommandBufferHandle buffer) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandEndRenderPass, commandFunctions, buffer);
}

void checkCommandBindGraphicsPipeline(gnCommandBufferHandle buffer, gnGraphicsPipelineHandle graphicsPipeline) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandBindGraphicsPipeline, commandFunctions, buffer, graphicsPipeline);
}
void checkCommandSetViewport(gnCommandBufferHandle buffer, gnViewport viewport) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandSetViewport, commandFunctions, buffer, viewport);
}
void checkCommandSetScissor(gnCommandBufferHandle buffer, gnScissor scissor) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandSetScissor, commandFunctions, buffer, scissor);
}
void checkCommandBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set, uint32_t dynamicOffsetCount, uint32_t* dynamicOffsets) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandBindUniform, commandFunctions, buffer, uniform, set, dynamicOffsetCount, dynamicOffsets);
}
void checkCommandPushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandPushConstant, commandFunctions, buffer, layout, data);
}

void checkCommandBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandBindBuffer, commandFunctions, buffer, bufferToBind, type);
}
void checkCommandDraw(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandDraw, commandFunctions, buffer, vertexCount, firstVertex, instanceCount, firstInstance);
}
void checkCommandDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance) {
    CHECK_VOID_FUNCTION(buffer->instance, _gnCommandDrawIndexed, commandFunctions, buffer, type, indexCount, firstIndex, vertexOffset, instanceCount, firstInstance);
}
