#pragma once
#include "command/command_buffer/gryphn_command_buffer.h"
#include "pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#import <Metal/MTLCommandBuffer.h>
#import <Metal/MTLCommandEncoder.h>

typedef struct gnPlatformCommandBuffer_t {
    id<MTLCommandBuffer> commandBuffer;
    id<MTLCommandEncoder> encoder;
    gnGraphicsPipeline boundGraphcisPipeline;
    gnBufferHandle indexBuffer;
} gnPlatformCommandBuffer;

gnReturnCode allocateMetalCommandBuffers(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPool pool);
void resetMetalCommandBuffer(gnCommandBuffer commandBuffer);
gnReturnCode beginMetalCommandBuffer(gnCommandBuffer commandBuffer);
gnReturnCode endMetalCommandBuffer(gnCommandBuffer commandBuffer);
