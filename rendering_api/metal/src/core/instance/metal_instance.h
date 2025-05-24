#pragma once
#include <Metal/MTLRenderPipeline.h>
#include <AppKit/AppKit.h>

typedef struct gnPlatformInstance_t {
    NSView* metalContentView;
    id<MTLRenderPipelineState> framebufferRenderer;
} gnPlatformInstance;
