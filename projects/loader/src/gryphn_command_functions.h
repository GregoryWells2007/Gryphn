#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "gryphn_handles.h"

typedef struct gnRenderPassInfo gnRenderPassInfo;
typedef struct gnViewport gnViewport;
typedef struct gnScissor gnScissor;
typedef struct gnPushConstantLayout gnPushConstantLayout;
typedef enum gnBufferType gnBufferType;
typedef enum gnIndexType gnIndexType;

typedef struct gnCommandFunctions_t {
    gnReturnCode (*_gnCommandPoolAllocateCommandBuffers)(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool);
    gnReturnCode (*_gnBeginCommandBuffer)(gnCommandBufferHandle commandBuffer);
    void (*_gnResetCommandBuffer)(gnCommandBufferHandle commandBuffer);
    gnReturnCode (*_gnEndCommandBuffer)(gnCommandBufferHandle commandBuffer);
    void (*_gnDestroyCommandBuffer)(gnCommandBufferHandle commandBuffer);

    void (*_gnCommandBeginRenderPass)(gnCommandBufferHandle buffer, gnRenderPassInfo passInfo);
    void (*_gnCommandEndRenderPass)(gnCommandBufferHandle buffer);

    void (*_gnCommandBindGraphicsPipeline)(gnCommandBufferHandle buffer, gnGraphicsPipelineHandle graphicsPipeline);
    void (*_gnCommandSetViewport)(gnCommandBufferHandle buffer, gnViewport viewport);
    void (*_gnCommandSetScissor)(gnCommandBufferHandle buffer, gnScissor scissor);
    void (*_gnCommandBindUniform)(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set, uint32_t dynamicOffsetCount, uint32_t* dynamicOffsets);
    void (*_gnCommandPushConstant)(gnCommandBufferHandle buffer, gnPushConstantLayout layout, void* data);

    void (*_gnCommandBindBuffer)(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type);
    void (*_gnCommandDraw)(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
    void (*_gnCommandDrawIndexed)(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance);
} gnCommandFunctions;
