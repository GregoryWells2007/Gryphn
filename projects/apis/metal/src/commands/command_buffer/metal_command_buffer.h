#pragma once
#include "core/command/command_buffer/gryphn_command_buffer.h"
#include "core/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#import <Metal/MTLCommandBuffer.h>
#import <Metal/MTLCommandEncoder.h>

typedef struct gnPlatformCommandBuffer_t {
    id<MTLCommandBuffer> commandBuffer;
    id<MTLCommandEncoder> encoder;
    struct gnGraphicsPipeline_t* boundGraphcisPipeline;
    gnBufferHandle indexBuffer;
} gnPlatformCommandBuffer;
