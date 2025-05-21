#pragma once
#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>

struct GLFWwindow;

struct gnPlatformInstance {
    NS::View* metalContentView;
    MTL::RenderPipelineState* framebufferRenderer, *testSquareRenderer;
};
