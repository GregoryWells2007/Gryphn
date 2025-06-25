#pragma once
#include "instance/gryphn_instance.h"
#include "output_device/gryphn_output_device.h"
#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>

struct gnPlatformPhysicalDevice_t {
    id<MTLDevice> device;
} gnPlatformPhysicalDevice;

struct gnPlatformOutputDevice_t {
    id<MTLDevice> device;
    MTKView* contentView;

    id<MTLCommandBuffer> executingCommandBuffer;
    id<MTLCommandQueue> transferQueue;
    // id<MTLRenderPipelineState> framebuffer;
} gnPlatformOutputDevice;
