#pragma once
#include "pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "shader_module/metal_shader_module.h"
#import <Metal/Metal.h>

typedef struct gnPlatformGraphicsPipeline_t {
    id<MTLRenderPipelineState> graphicsPipeline;
    id<MTLDepthStencilState> depthState;
} gnPlatformGraphicsPipeline;

gnReturnCode createMetalGraphicsPipeline(gnGraphicsPipeline graphicsPipeline, gnOutputDevice device, gnGraphicsPipelineInfo info);
void destroyMetalGraphicsPipeline(gnGraphicsPipeline graphicsPipeline);
