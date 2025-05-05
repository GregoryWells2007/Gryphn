#include <core/graphics_pipeline/gryphn_render_pass_frame.h>
#include <Metal/Metal.hpp>

struct gnPlatformRenderPassFrame {
    // ive been told I can recreate this jazz every frame so im going to do that, screw you
    MTL::RenderPassDescriptor* renderPassDescriptor = nullptr;
    MTL::RenderCommandEncoder* renderCommandEncoder = nullptr;

    gnColor clearColor;

    gnPlatformRenderPassFrame();
};
