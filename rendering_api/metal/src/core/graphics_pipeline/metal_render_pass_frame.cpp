#include <core/graphics_pipeline/gryphn_render_pass_frame.h>
#include "metal_render_pass_frame.h"
#include <Metal/Metal.hpp>

gnPlatformRenderPassFrame::gnPlatformRenderPassFrame() {
    // renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();
}

GN_EXPORT void gnRenderPassFrameSetRenderPassFn(gnRenderPassFrame& frame, const gnRenderPass& renderPass) {
    if (frame.renderPassFrame == nullptr) frame.renderPassFrame = new gnPlatformRenderPassFrame();
    // this is going to do nothing
}
GN_EXPORT void gnRenderPassFrameSetFramebufferFn(gnRenderPassFrame& frame, const gnFramebuffer& framebuffer) {
    if (frame.renderPassFrame == nullptr) frame.renderPassFrame = new gnPlatformRenderPassFrame();
    std::cout << "gnRenderPassFrameSetFramebufferFn on Metal is not implemented, il do this at some point\n";
    // this will do something with setting the attachment descriptions but im kinda lazy
    // and by lazy I mean gnFramebuffer_metal_impl has not been created yet
}
GN_EXPORT void gnRenderPassFrameSetOffsetFn(gnRenderPassFrame& frame, const gnUInt2& offset) {
    if (frame.renderPassFrame == nullptr) frame.renderPassFrame = new gnPlatformRenderPassFrame();
    //frame.renderPassFrame->renderPassDescriptor->
    if (offset.x != 0 || offset.y != 0) std::cout << "gnRenderPassFrameOffsetFn offset must be zero on metal\n";
}
GN_EXPORT void gnRenderPassFrameSetRenderAreaFn(gnRenderPassFrame& frame, const gnUInt2& area){
    if (frame.renderPassFrame == nullptr) frame.renderPassFrame = new gnPlatformRenderPassFrame();
    frame.renderPassFrame->renderPassDescriptor->setRenderTargetWidth(area.x);
    frame.renderPassFrame->renderPassDescriptor->setRenderTargetHeight(area.y);
}
GN_EXPORT void gnRenderPassFrameSetClearColorFn(gnRenderPassFrame& frame, gnColor clearColor) {
    if (frame.renderPassFrame == nullptr) frame.renderPassFrame = new gnPlatformRenderPassFrame();
    std::cout << "gnRenderPassFrameSetClearColorFn does nothing on metal cuz imma bitch\n";
}
