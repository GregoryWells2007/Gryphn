#include "opengl_render_pass_descriptor.h"
#include "surface/opengl_surface.h"
#include "stdlib.h"

gnReturnCode openglCreateRenderPass(gnRenderPassDescriptor renderPass, gnDevice device, gnRenderPassDescriptorInfo info) {
    if (device == GN_NULL_HANDLE) return GN_INVALID_HANDLE;
    renderPass->renderPassDescriptor = malloc(sizeof(gnPlatformRenderPassDescriptor));
    renderPass->renderPassDescriptor->subpassCount = info.subpassCount;
    renderPass->renderPassDescriptor->subpasses = malloc(sizeof(glSubpass) * info.subpassCount);

    for (uint32_t i = 0; i < info.subpassCount; i++) {
        renderPass->renderPassDescriptor->subpasses[i] = (glSubpass){
            .colorAttachmentCount = info.subpassInfos[i].colorAttachmentCount,
            .colorAttachments = malloc(sizeof(glColorAttachment) * info.subpassInfos[i].colorAttachmentCount),
            .depthAttachment.index = -1
        };
        gnBool resolve = !(info.subpassInfos[i].resolveAttachments == NULL);
        for (uint32_t c = 0; c < info.subpassInfos[i].colorAttachmentCount; c++) {
            uint32_t attachmentIndex = info.subpassInfos[i].colorAttachments[c].index;
            int resolveAttachmentIndex = -1;
            if (resolve)
                resolveAttachmentIndex = info.subpassInfos[i].resolveAttachments[c].index;

            renderPass->renderPassDescriptor->subpasses[i].colorAttachments[c] = (glColorAttachment){
                .loadOperation  = info.attachmentInfos[attachmentIndex].loadOperation,
                .storeOperation = info.attachmentInfos[attachmentIndex].storeOperation,
                .attachmentIndex = attachmentIndex,
                .resolveAttachmentIndex = resolveAttachmentIndex,
                .format = glGryphnFormatToOpenGLFormat(info.attachmentInfos[attachmentIndex].format)
            };
        }

        if (info.subpassInfos[i].depthAttachment != NULL) {
            uint32_t depthAttachmentIndex = info.subpassInfos[i].depthAttachment->index;
            renderPass->renderPassDescriptor->subpasses[i].depthAttachment = (gnDepthAttachment){
                .index = depthAttachmentIndex,
                .format = glGryphnFormatToOpenGLFormat(info.attachmentInfos[depthAttachmentIndex].format),
                .loadOperation  = info.attachmentInfos[depthAttachmentIndex].loadOperation,
                .storeOperation = info.attachmentInfos[depthAttachmentIndex].storeOperation,
            };
        }
    }
    return GN_SUCCESS;
}
void openglDestroyRenderPass(gnRenderPassDescriptor renderPass) {
    for (int i = 0; i < renderPass->renderPassDescriptor->subpassCount; i++)
        free(renderPass->renderPassDescriptor->subpasses[i].colorAttachments);
    free(renderPass->renderPassDescriptor->subpasses);
    free(renderPass->renderPassDescriptor);
}
