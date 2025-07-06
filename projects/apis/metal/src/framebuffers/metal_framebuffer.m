#include "metal_framebuffer.h"
#include "debugger/gryphn_debugger.h"
#include "texture/metal_texture.h"
#include "renderpass/gryphn_render_pass_descriptor.h"
#include "instance/gryphn_instance.h"
#include "output_device/gryphn_output_device.h"

gnBool isDepthFormat(gnImageFormat format) {
    return (format == GN_FORMAT_D24S8_UINT) || (format == GN_FORMAT_D32S8_UINT);
}

gnBool isStencilFormat(gnImageFormat format) {
    return (format == GN_FORMAT_D24S8_UINT) || (format == GN_FORMAT_D32S8_UINT);
}

MTLLoadAction mtlGryphnLoadOperation(gnLoadOperation loadOperation) {
    switch(loadOperation) {
    case GN_LOAD_OPERATION_LOAD: return MTLLoadActionLoad;
    case GN_LOAD_OPERATION_CLEAR: return MTLLoadActionClear;
    case GN_LOAD_OPERATION_DONT_CARE: return MTLLoadActionDontCare;
    }
}

MTLStoreAction mtlGryphnStoreOperation(gnStoreOperation storeOperation) {
    switch (storeOperation) {
    case GN_STORE_OPERATION_STORE: return MTLStoreActionStore;
    case GN_STORE_OPERATION_DONT_CARE: return MTLStoreActionDontCare;
    }
}

gnReturnCode createMetalFramebuffer(gnFramebuffer framebuffer, gnOutputDevice device, gnFramebufferInfo info) {
    framebuffer->framebuffer = malloc(sizeof(struct gnPlatformFramebuffer_t));
    if (info.attachmentCount != info.renderPassDescriptor->info.attachmentCount) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Attachment count on framebuffer does not equal attachment count on render pass descriptor")
        });
        return GN_DIVERGENT_RENDERPASS;
    }

    framebuffer->framebuffer->subpassCount = info.renderPassDescriptor->info.subpassCount;
    framebuffer->framebuffer->subpasses = malloc(sizeof(mtlSubpass) * framebuffer->framebuffer->subpassCount);

    for (int i = 0; i < info.renderPassDescriptor->info.subpassCount; i++) {
        framebuffer->framebuffer->subpasses[i] = [[MTLRenderPassDescriptor alloc] init];
        [framebuffer->framebuffer->subpasses[i] setRenderTargetWidth:info.size.x];
        [framebuffer->framebuffer->subpasses[i] setRenderTargetHeight:info.size.y];

        for (int c = 0; c < info.renderPassDescriptor->info.subpassInfos[i].colorAttachmentCount; c++) {
            uint32_t attachmentIndex = info.renderPassDescriptor->info.subpassInfos[i].colorAttachments[i].index;
            MTLRenderPassColorAttachmentDescriptor* color = framebuffer->framebuffer->subpasses[i].colorAttachments[c];
            color.texture = info.attachments[attachmentIndex]->texture->texture;

            color.loadAction  = mtlGryphnLoadOperation(info.renderPassDescriptor->info.attachmentInfos[attachmentIndex].loadOperation);
            color.storeAction = mtlGryphnStoreOperation(info.renderPassDescriptor->info.attachmentInfos[attachmentIndex].storeOperation);

            if (color.loadAction == MTLLoadActionClear)
                color.clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);
        }

        if (info.renderPassDescriptor->info.subpassInfos[i].depthAttachment != NULL) {
            MTLRenderPassDepthAttachmentDescriptor* depthAttachment = framebuffer->framebuffer->subpasses[i].depthAttachment;
            uint32_t attachmentIndex = info.renderPassDescriptor->info.subpassInfos[i].depthAttachment->index;
            depthAttachment.texture = info.attachments[attachmentIndex]->texture->texture;
            depthAttachment.loadAction  = mtlGryphnLoadOperation(info.renderPassDescriptor->info.attachmentInfos[attachmentIndex].loadOperation);
            depthAttachment.storeAction = mtlGryphnStoreOperation(info.renderPassDescriptor->info.attachmentInfos[attachmentIndex].storeOperation);
            depthAttachment.clearDepth = 1.0f;

            MTLRenderPassStencilAttachmentDescriptor* stencilAttachment = framebuffer->framebuffer->subpasses[attachmentIndex].stencilAttachment;
            stencilAttachment.texture = info.attachments[i]->texture->texture;
        }
    }

    return GN_SUCCESS;
}

void destroyMetalFramebuffer(gnFramebuffer framebuffer) {
    for (int i = 0; i < framebuffer->framebuffer->subpassCount; i++) [framebuffer->framebuffer->subpasses[i] release];
    free(framebuffer->framebuffer->subpasses);
    free(framebuffer->framebuffer);
}
