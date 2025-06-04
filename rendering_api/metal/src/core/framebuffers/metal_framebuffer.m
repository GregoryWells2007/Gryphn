#include "metal_framebuffer.h"
#include "core/debugger/gryphn_debugger.h"
#include "core/texture/metal_texture.h"
#include "core/renderpass/gryphn_render_pass_descriptor.h"

gnBool isDepthFormat(gnImageFormat format) {
    return gnFalse;
}

gnBool isStencilFormat(gnImageFormat format) {
    return gnFalse;
}

MTLLoadAction mtlGryphnLoadOperation(enum gnLoadOperation_e loadOperation) {
    switch(loadOperation) {
    case GN_LOAD_OPERATION_LOAD: return MTLLoadActionLoad;
    case GN_LOAD_OPERATION_CLEAR: return MTLLoadActionClear;
    case GN_LOAD_OPERATION_DONT_CARE: return MTLLoadActionDontCare;
    }
}

MTLStoreAction mtlGryphnStoreOperation(enum gnStoreOperation_e storeOperation) {
    switch (storeOperation) {
    case GN_STORE_OPERATION_STORE: return MTLStoreActionStore;
    case GN_STORE_OPERATION_DONT_CARE: return MTLStoreActionDontCare;
    }
}

gnReturnCode gnCreateFramebufferFn(struct gnFramebuffer_t* framebuffer, struct gnOutputDevice_t* device, struct gnFramebufferInfo_t info) {
    framebuffer->framebuffer = malloc(sizeof(struct gnPlatformFramebuffer_t));
    if (info.attachmentCount != info.renderPassDescriptor->info.attachmentCount) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Attachment count on framebuffer does not equal attachment count on render pass descriptor")
        });
        return GN_DIVERGENT_RENDERPASS;
    }

    framebuffer->framebuffer->framebuffer = [[MTLRenderPassDescriptor alloc] init];
    [framebuffer->framebuffer->framebuffer setRenderTargetWidth:info.size.x];
    [framebuffer->framebuffer->framebuffer setRenderTargetHeight:info.size.y];

    int colorAttachment = 0;
    for (int i = 0; i < info.renderPassDescriptor->info.attachmentCount; i++) {
        gnBool wasDepthStencil = gnFalse;
        if (isDepthFormat(info.renderPassDescriptor->info.attachmentInfos[i].format)) {
            gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
                .message = gnCreateString("Depth attachments are not currently supported in metal (get on this)")
            });
            wasDepthStencil = gnTrue;
        }
        if (isStencilFormat(info.renderPassDescriptor->info.attachmentInfos[i].format)) {
            gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
                .message = gnCreateString("Stencil attachments are not currently supported in metal (get on this)")
            });
            wasDepthStencil = gnTrue;
        }

        if(!wasDepthStencil) {
            MTLRenderPassColorAttachmentDescriptor* color = framebuffer->framebuffer->framebuffer.colorAttachments[colorAttachment];
            color.texture = info.attachments[i]->texture->texture;

            color.loadAction  = mtlGryphnLoadOperation(info.renderPassDescriptor->info.attachmentInfos[i].loadOperation);
            color.storeAction = mtlGryphnStoreOperation(info.renderPassDescriptor->info.attachmentInfos[i].storeOperation);

            if (color.loadAction == MTLLoadActionClear)
                color.clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);

            colorAttachment++;
        }
    }

    return GN_SUCCESS;
}

void gnDestroyFramebufferFn(struct gnFramebuffer_t* framebuffer) {
    [framebuffer->framebuffer->framebuffer release];
    free(framebuffer->framebuffer);
}
