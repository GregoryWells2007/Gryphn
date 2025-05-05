#pragma once
#ifndef OBJECT_C_CODE
#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalLayer.hpp>
#include <QuartzCore/CAMetalLayer.h>
#include <QuartzCore/QuartzCore.hpp>

#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include <Foundation/Foundation.hpp>
#endif

struct GLFWwindow;

struct gnPlatformInstanceData {
    NS::Window* metalWindow;
    NS::View* metalContentView;
    GLFWwindow* window;

    MTL::RenderPipelineState* framebufferRenderer, *testSquareRenderer;
};
