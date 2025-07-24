#include "metal_framebuffer.h"
#include "texture/metal_texture.h"
#include "renderpass/gryphn_render_pass_descriptor.h"
#include "instance/gryphn_instance.h"
#include "output_device/gryphn_output_device.h"
#include "utils/gryphn_image_format.h"
gnReturnCode createMetalFramebuffer(gnFramebuffer framebuffer, gnOutputDevice device, gnFramebufferInfo info) {
    framebuffer->framebuffer = malloc(sizeof(struct gnPlatformFramebuffer_t));

    framebuffer->framebuffer->clearCopyCount = info.attachmentCount;
    framebuffer->framebuffer->clearCopies = malloc(sizeof(mtlClearCopy) * info.attachmentCount);
    for (int i = 0; i < info.attachmentCount; i++) {
        framebuffer->framebuffer->clearCopies[i].clear = gnFalse;
    }

    framebuffer->framebuffer->subpassCount = info.renderPassDescriptor->renderPassDescriptor->subpassCount;
    framebuffer->framebuffer->subpasses = malloc(sizeof(mtlSubpass) * framebuffer->framebuffer->subpassCount);
    framebuffer->framebuffer->depthAttachmentIndicies = malloc(sizeof(uint32_t) * framebuffer->framebuffer->subpassCount);
    for (int i = 0; i < framebuffer->framebuffer->subpassCount; i++) {
        framebuffer->framebuffer->subpasses[i] = [info.renderPassDescriptor->renderPassDescriptor->subpasses[i] copy];
        MTLRenderPassDescriptor* pass = framebuffer->framebuffer->subpasses[i];
        [pass setRenderTargetWidth:info.size.x];
        [pass setRenderTargetHeight:info.size.y];

        for (int c = 0; c < info.renderPassDescriptor->renderPassDescriptor->copyInfos[i].colorAttachmentCount; c++) {
            MTLRenderPassColorAttachmentDescriptor* colorPass = pass.colorAttachments[c];
            colorPass.texture = info.attachments[info.renderPassDescriptor->renderPassDescriptor->copyInfos[i].colorAttachments[c].attachmentIndex]->texture->texture;
            if (info.renderPassDescriptor->renderPassDescriptor->copyInfos[i].colorAttachments[c].resolveAttachmentIndex >= 0)
                colorPass.resolveTexture = info.attachments[info.renderPassDescriptor->renderPassDescriptor->copyInfos[i].colorAttachments[c].resolveAttachmentIndex]->texture->texture;
            framebuffer->framebuffer->clearCopies[info.renderPassDescriptor->renderPassDescriptor->copyInfos[i].colorAttachments[c].attachmentIndex].clear = gnTrue;
            framebuffer->framebuffer->clearCopies[info.renderPassDescriptor->renderPassDescriptor->copyInfos[i].colorAttachments[c].attachmentIndex].descriptor = colorPass;
        }

        if (info.renderPassDescriptor->renderPassDescriptor->copyInfos[i].depthAttachmentIndex >= 0) {
            MTLRenderPassDepthAttachmentDescriptor* depthAttachment = framebuffer->framebuffer->subpasses[i].depthAttachment;
            depthAttachment.texture = info.attachments[info.renderPassDescriptor->renderPassDescriptor->copyInfos[i].depthAttachmentIndex]->texture->texture;
        }

        // if (info.attachments[i]->info.format == GN_FORMAT_D24S8_UINT || info.attachments[i]->info.format == GN_FORMAT_D32S8_UINT) {
        //     framebuffer->framebuffer->depthAttachmentIndicies[i] = i;
        //     MTLRenderPassStencilAttachmentDescriptor* stencilAttachment = framebuffer->framebuffer->subpasses[i].stencilAttachment;
        //     stencilAttachment.texture = info.attachments[i]->texture->texture;
        // }
    }

    return GN_SUCCESS;
}

void destroyMetalFramebuffer(gnFramebuffer framebuffer) {
    for (int i = 0; i < framebuffer->framebuffer->subpassCount; i++) [framebuffer->framebuffer->subpasses[i] release];
    free(framebuffer->framebuffer->subpasses);
    free(framebuffer->framebuffer);
}
