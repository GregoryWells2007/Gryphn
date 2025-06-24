#pragma once
// theoretically you could have multible gryphn instances running in one application,
// why I dont know
#include "instance/gryphn_instance.h"
#include <debugger/gryphn_debugger.h>
#include <window_surface/gryphn_surface_create_functions.h>
#include "pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "renderpass/gryphn_render_pass.h"
#include "buffers/gryphn_buffer.h"

typedef struct gnCommandFunctions_t {
    gnReturnCode (*_gnCommandPoolAllocateCommandBuffers)(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool);
    gnReturnCode (*_gnBeginCommandBuffer)(gnCommandBufferHandle commandBuffer);
    void (*_gnResetCommandBuffer)(gnCommandBufferHandle commandBuffer);
    gnReturnCode (*_gnEndCommandBuffer)(gnCommandBufferHandle commandBuffer);

    void (*_gnCommandBeginRenderPass)(gnCommandBufferHandle buffer, gnRenderPassInfo passInfo);
    void (*_gnCommandEndRenderPass)(gnCommandBufferHandle buffer);

    void (*_gnCommandBindGraphicsPipeline)(gnCommandBufferHandle buffer, gnGraphicsPipelineHandle graphicsPipeline);
    void (*_gnCommandSetViewport)(gnCommandBufferHandle buffer, gnViewport viewport);
    void (*_gnCommandSetScissor)(gnCommandBufferHandle buffer, gnScissor scissor);
    void (*_gnCommandBindUniform)(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set);
    void (*_gnCommandPushConstant)(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);

    void (*_gnCommandBindBuffer)(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);
    void (*_gnCommandDraw)(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
    void (*_gnCommandDrawIndexed)(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
} gnCommandFunctions;
