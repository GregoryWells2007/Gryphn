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

    id<MTLBuffer> fullScreenQuadBuffer;
    id<MTLLibrary> fullScreenShader;
    id<MTLFunction> fullScreenVertex, fullScreenFragment;
    id<MTLRenderPipelineState> fullScreenPipeline;
} gnPlatformOutputDevice;

gnPhysicalDevice* getMetalDevices(gnInstanceHandle instance, uint32_t* deviceCount);
gnBool metalCanDevicePresent(gnPhysicalDevice device, gnWindowSurface windowSurface);

gnReturnCode createMetalOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle outputDevice, gnOutputDeviceInfo deviceInfo);
void waitForMetalDevice(gnOutputDeviceHandle device);
void destroyMetalOutputDevice(gnOutputDeviceHandle device);
