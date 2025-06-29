#include "command_functions.h"
#include "core/src/command/command_pool/gryphn_command_pool.h"
#include "core/src/command/command_buffer/gryphn_command_buffer.h"
#include "core/src/output_device/gryphn_output_device.h"
#include <core/src/debugger/gryphn_debugger.h>
#include <core/src/instance/gryphn_instance.h>
#include "core/src/renderpass/gryphn_render_pass.h"
#include "core/src/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "core/src/buffers/gryphn_buffer.h"
#include "loader_utils.h"

gnReturnCode checkCommandPoolAllocateCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool) {
    CHECK_FUNCTION_WITH_RETURN_CODE_COMMAND(pool->device->instance, _gnCommandPoolAllocateCommandBuffers, commandBuffers, count, pool);
}
gnReturnCode checkBeginCommandBuffer(gnCommandBufferHandle commandBuffer) {
    CHECK_FUNCTION_WITH_RETURN_CODE_COMMAND(commandBuffer->instance, _gnBeginCommandBuffer, commandBuffer);
}
void checkResetCommandBuffer(gnCommandBufferHandle commandBuffer) {
    CHECK_VOID_FUNCTION_COMMAND(commandBuffer->instance, _gnResetCommandBuffer, commandBuffer);
}
gnReturnCode checkEndCommandBuffer(gnCommandBufferHandle commandBuffer) {
    CHECK_FUNCTION_WITH_RETURN_CODE_COMMAND(commandBuffer->instance, _gnEndCommandBuffer, commandBuffer);
}

void checkCommandBeginRenderPass(gnCommandBufferHandle buffer, gnRenderPassInfo passInfo) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandBeginRenderPass, buffer, passInfo);
}
void checkCommandEndRenderPass(gnCommandBufferHandle buffer) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandEndRenderPass, buffer);
}

void checkCommandBindGraphicsPipeline(gnCommandBufferHandle buffer, gnGraphicsPipelineHandle graphicsPipeline) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandBindGraphicsPipeline, buffer, graphicsPipeline);
}
void checkCommandSetViewport(gnCommandBufferHandle buffer, gnViewport viewport) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandSetViewport, buffer, viewport);
}
void checkCommandSetScissor(gnCommandBufferHandle buffer, gnScissor scissor) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandSetScissor, buffer, scissor);
}
void checkCommandBindUniform(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandBindUniform, buffer, uniform, set);
}
void checkCommandPushConstant(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandPushConstant, buffer, layout, data);
}

void checkCommandBindBuffer(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandBindBuffer, buffer, bufferToBind, type);
}
void checkCommandDraw(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandDraw, buffer, vertexCount, firstVertex, instanceCount, firstInstance);
}
void checkCommandDrawIndexed(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance) {
    CHECK_VOID_FUNCTION_COMMAND(buffer->instance, _gnCommandDrawIndexed, buffer, type, indexCount, firstIndex, vertexOffset, instanceCount, firstInstance);
}
