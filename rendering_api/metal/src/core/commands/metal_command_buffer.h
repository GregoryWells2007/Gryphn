#pragma once
#include <core/commands/gryphn_command_buffer.h>
#include <core/graphics_pipeline/gryphn_graphics_pipeline.h>
#include <Metal/Metal.hpp>

struct gnPlatformCommandBuffer {
    MTL::CommandBuffer* commandBuffer;
    MTL::RenderCommandEncoder* renderCommandEncoder;

    MTL::Buffer* boundIndexBuffer = nullptr;

    const gnOutputDevice* outputDevice;
};
