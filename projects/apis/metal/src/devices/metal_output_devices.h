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
} gnPlatformOutputDevice;

gnPhysicalDevice* getMetalDevices(gnInstanceHandle instance, uint32_t* deviceCount);
gnBool metalCanQueuePresentToSurface(const gnPhysicalDevice device, uint32_t queueIndex, gnWindowSurface windowSurface);

gnReturnCode createMetalOutputDevice(gnOutputDeviceHandle outputDevice, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo);
void waitForMetalDevice(gnOutputDeviceHandle device);
void destroyMetalOutputDevice(gnOutputDeviceHandle device);
