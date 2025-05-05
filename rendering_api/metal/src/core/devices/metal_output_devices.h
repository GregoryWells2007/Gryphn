#pragma once
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

struct gnPlatformPhysicalOutputDevice {
    MTL::Device* device;
};
struct gnInstance;

struct gnPlatformOutputDevice {
    MTL::Device* device;
    MTL::CommandQueue* commandQueue;
    MTK::View* contentView;

    gnInstance* instance;
};
