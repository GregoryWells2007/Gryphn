#pragma once
#include "pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#import <Metal/Metal.h>

typedef struct gnPlatformGraphicsPipeline_t {
    id<MTLRenderPipelineState> graphicsPipeline;
} gnPlatformGraphicsPipeline;

gnReturnCode createMetalGraphicsPipeline(gnGraphicsPipeline graphicsPipeline, gnOutputDevice device, gnGraphicsPipelineInfo info);
void destroyMetalGraphicsPipeline(gnGraphicsPipeline graphicsPipeline);
