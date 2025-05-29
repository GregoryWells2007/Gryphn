#pragma once
#include "core/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#import <Metal/Metal.h>

typedef struct gnPlatformGraphicsPipeline_t {
    id<MTLRenderPipelineState> graphicsPipeline;
} gnPlatformGraphicsPipeline;
