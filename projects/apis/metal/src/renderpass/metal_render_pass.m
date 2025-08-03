#include "metal_render_pass.h"

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

MTLStoreAction mtlGryphnStoreOperationResolve(gnStoreOperation storeOperation) {
    switch (storeOperation) {
    case GN_STORE_OPERATION_STORE: return MTLStoreActionStoreAndMultisampleResolve;
    case GN_STORE_OPERATION_DONT_CARE: return MTLStoreActionDontCare;
    }
}

gnReturnCode createMetalRenderPass(gnRenderPassDescriptor renderPass, gnDevice device, gnRenderPassDescriptorInfo info) {
    if (device == GN_NULL_HANDLE) return GN_INVALID_HANDLE;

    renderPass->renderPassDescriptor = malloc(sizeof(gnPlatformRenderPassDescriptor));
    renderPass->renderPassDescriptor->subpassCount = info.subpassCount;
    renderPass->renderPassDescriptor->subpasses = malloc(sizeof(mtlSubpass) * info.subpassCount);
    renderPass->renderPassDescriptor->copyInfos = malloc(sizeof(mtlSubpassCopyInfo) * info.subpassCount);

    for (uint32_t i = 0; i < info.subpassCount; i++) {
        renderPass->renderPassDescriptor->subpasses[i] = [[MTLRenderPassDescriptor alloc] init];
        gnBool resolve = !(info.subpassInfos[i].resolveAttachments == NULL);
        renderPass->renderPassDescriptor->copyInfos[i].colorAttachmentCount = info.subpassInfos[i].colorAttachmentCount;
        renderPass->renderPassDescriptor->copyInfos[i].colorAttachments = malloc(sizeof(mtlColorAttachmentCopyInfo) * info.subpassInfos[i].colorAttachmentCount);
        for (uint32_t c = 0; c < info.subpassInfos[i].colorAttachmentCount; c++) {
            uint32_t attachmentIndex = info.subpassInfos[i].colorAttachments[c].index;
            int resolveAttachmentIndex = -1;

            renderPass->renderPassDescriptor->subpasses[i].colorAttachments[c] = [[MTLRenderPassColorAttachmentDescriptor alloc] init];
            MTLRenderPassColorAttachmentDescriptor* color = renderPass->renderPassDescriptor->subpasses[i].colorAttachments[c];
            if (resolve) {
                resolveAttachmentIndex = info.subpassInfos[i].resolveAttachments[c].index;
                color.storeAction = mtlGryphnStoreOperationResolve(info.attachmentInfos[attachmentIndex].storeOperation);
            } else
                color.storeAction = mtlGryphnStoreOperation(info.attachmentInfos[attachmentIndex].storeOperation);
            color.loadAction  = mtlGryphnLoadOperation(info.attachmentInfos[attachmentIndex].loadOperation);
            color.storeAction = MTLStoreActionStoreAndMultisampleResolve;

            if (color.loadAction == MTLLoadActionClear)
                color.clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);

            renderPass->renderPassDescriptor->copyInfos[i].colorAttachments[c].format = MTLPixelFormatBGRA8Unorm_sRGB;
            renderPass->renderPassDescriptor->copyInfos[i].colorAttachments[c].attachmentIndex = attachmentIndex;
            renderPass->renderPassDescriptor->copyInfos[i].colorAttachments[c].resolveAttachmentIndex = resolveAttachmentIndex;
        }

        renderPass->renderPassDescriptor->copyInfos[i].depthAttachmentIndex = -1;
        if (info.subpassInfos[i].depthAttachment != NULL) {
            MTLRenderPassDepthAttachmentDescriptor* depthAttachment = renderPass->renderPassDescriptor->subpasses[i].depthAttachment;
            uint32_t attachmentIndex = info.subpassInfos[i].depthAttachment->index;
            depthAttachment.loadAction  = mtlGryphnLoadOperation(info.attachmentInfos[attachmentIndex].loadOperation);
            depthAttachment.storeAction = mtlGryphnStoreOperation(info.attachmentInfos[attachmentIndex].storeOperation);
            depthAttachment.clearDepth = 1.0f;
            renderPass->renderPassDescriptor->copyInfos[i].depthAttachmentIndex = attachmentIndex;
        }
    }
    return GN_SUCCESS;
}

void destroyMetalRenderPass(gnRenderPassDescriptor renderPass) {
    for (uint32_t i = 0; i < renderPass->renderPassDescriptor->subpassCount; i++) {
        [renderPass->renderPassDescriptor->subpasses[i] release];
        for (uint32_t c = 0; c < renderPass->renderPassDescriptor->copyInfos[i].colorAttachmentCount; c++)
            free(renderPass->renderPassDescriptor->copyInfos[i].colorAttachments);
    }
    free(renderPass->renderPassDescriptor->copyInfos);
    free(renderPass->renderPassDescriptor);
}
