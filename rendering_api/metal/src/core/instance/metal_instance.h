#pragma once
#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>

struct GLFWwindow;

typedef struct gnPlatformInstance_t {
    NS::View* metalContentView;
    MTL::RenderPipelineState* framebufferRenderer, *testSquareRenderer;
} gnPlatformInstance;
