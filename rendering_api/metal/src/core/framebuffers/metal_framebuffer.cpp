#include "metal_framebuffer.h"
#include "core/graphics_pipeline/metal_graphics_pipeline.h"
#include <core/devices/metal_output_devices.h>
#include <core/textures/metal_texture.h>

GN_EXPORT gnReturnCode gnCreateFramebufferAttachmentFn(gnFramebufferAttachment* attachment, gnPresentationQueue& queue) {
    attachment->framebufferAttachment = new gnPlatformFramebufferAttachment();
    // attachment->framebufferAttachment->framebufferAttachment = MTL::RenderPassAttachmentDescriptor::alloc()->init();
    // MTL::RenderPassAttachmentDescriptor* descriptor = attachment->framebufferAttachment->framebufferAttachment;
    // attachment->framebufferAttachment->framebufferAttachment->setTexture(attachment->texture->texture->texture->retain());
    // descriptor->setLoadAction(MTL::LoadActionClear);
    // descriptor->setStoreAction(MTL::StoreActionStore);
    return GN_SUCCESS;
}

GN_EXPORT gnReturnCode gnCreateFramebufferFn(gnFramebuffer* framebuffer, const gnRenderPass& renderpass) {
    framebuffer->framebuffer = new gnPlatformFramebuffer();
    framebuffer->framebuffer->framebuffer = MTL::RenderPassDescriptor::alloc()->init();
    framebuffer->framebuffer->framebuffer->setRenderTargetWidth(framebuffer->size.x);
    framebuffer->framebuffer->framebuffer->setRenderTargetHeight(framebuffer->size.y);
    framebuffer->framebuffer->framebuffer->setDepthAttachment(nullptr);
    int currentColorAttachment = 0;
    for (int i = 0; i < gnListLength(framebuffer->framebufferAttachments); i++) {
        if (framebuffer->framebufferAttachments[i].bindPoint == GN_COLOR_ATTACHMENT) {
            MTL::RenderPassColorAttachmentDescriptor* colorAttachment = framebuffer->framebuffer->framebuffer->colorAttachments()->object(currentColorAttachment)->retain();
            colorAttachment->setTexture(framebuffer->framebufferAttachments[i].texture->texture->texture);
            colorAttachment->setClearColor(MTL::ClearColor::Make(1.0f, 0.0f, 0.0f, 1.0f));
            colorAttachment->setLoadAction(MTL::LoadActionClear);
            colorAttachment->setStoreAction(MTL::StoreActionStore);
            colorAttachment->release();
            currentColorAttachment++;
        } else if (framebuffer->framebufferAttachments[i].bindPoint == GN_DEPTH_STENCIL_ATTACHMENT) {
            MTL::RenderPassDepthAttachmentDescriptor* depthAttachment = framebuffer->framebuffer->framebuffer->depthAttachment()->retain();
            depthAttachment->setTexture(framebuffer->framebufferAttachments[i].texture->texture->texture);
            depthAttachment->setLoadAction(MTL::LoadActionClear);
            depthAttachment->setStoreAction(MTL::StoreActionStore);
            depthAttachment->release();

            MTL::RenderPassStencilAttachmentDescriptor* stencilAttachment = framebuffer->framebuffer->framebuffer->stencilAttachment()->retain();
            stencilAttachment->setTexture(framebuffer->framebufferAttachments[i].texture->texture->texture);
            stencilAttachment->setLoadAction(MTL::LoadActionClear);
            stencilAttachment->setStoreAction(MTL::StoreActionStore);
            stencilAttachment->release();
        } else {
            return gnReturnError(GN_UNKNOWN_FRAMEBUFFER_ATTACHMENT, "GN_DEPTH_ATTACHMENT and GN_STENCIL_ATTACHMENT are unsupported on metal for now");
        }
    }
    return GN_SUCCESS;
}
GN_EXPORT void gnDestroyFramebufferFn(const gnFramebuffer& framebuffer) {
    framebuffer.framebuffer->framebuffer->release();
}
