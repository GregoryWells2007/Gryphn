#include "vulkan_render_pass_descriptor.h"
#include "vulkan_surface/vulkan_surface.h"
#include "output_device/vulkan_output_devices.h"
#include "stdio.h"

VkAttachmentLoadOp vkGryphnLoadOperation(gnLoadOperation loadOperation) {
    switch(loadOperation) {
    case GN_LOAD_OPERATION_LOAD: return VK_ATTACHMENT_LOAD_OP_LOAD;
    case GN_LOAD_OPERATION_CLEAR: return VK_ATTACHMENT_LOAD_OP_CLEAR;
    case GN_LOAD_OPERATION_DONT_CARE: return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    }
}

VkAttachmentStoreOp vkGryphnStoreOperation(gnStoreOperation storeOperation) {
    switch (storeOperation) {
    case GN_STORE_OPERATION_STORE: return VK_ATTACHMENT_STORE_OP_STORE;
    case GN_STORE_OPERATION_DONT_CARE: return VK_ATTACHMENT_STORE_OP_DONT_CARE;
    }
}

VkImageLayout vkGryphnImageLayout(gnImageLayout layout) {
    switch(layout) {
    case GN_LAYOUT_UNDEFINED: return VK_IMAGE_LAYOUT_UNDEFINED;
    case GN_LAYOUT_PRESENTATION_QUEUE_IMAGE: return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    case GN_LAYOUT_TRANSFER_DESTINATION: return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    case GN_COLOR_ATTACHMENT: return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
}

gnReturnCode gnCreateRenderPassDescriptorFn(struct gnRenderPassDescriptor_t* renderPass, struct gnOutputDevice_t* device, struct gnRenderPassDescriptorInfo_t info) {
    renderPass->renderPassDescriptor = malloc(sizeof(gnPlatformRenderPassDescriptor));

    renderPass->renderPassDescriptor->attachmentCount = info.attachmentCount;
    renderPass->renderPassDescriptor->attachments = malloc(sizeof(VkAttachmentDescription) * info.attachmentCount);
    for (int i = 0; i < info.attachmentCount; i++) {
        renderPass->renderPassDescriptor->attachments[i].format = vkGryphnFormatToVulkanFormat(info.attachmentInfos[i].format);
        renderPass->renderPassDescriptor->attachments[i].flags = 0;
        renderPass->renderPassDescriptor->attachments[i].samples = VK_SAMPLE_COUNT_1_BIT;

        renderPass->renderPassDescriptor->attachments[i].loadOp = vkGryphnLoadOperation(info.attachmentInfos[i].loadOperation);
        renderPass->renderPassDescriptor->attachments[i].storeOp = vkGryphnStoreOperation(info.attachmentInfos[i].storeOperation);

        renderPass->renderPassDescriptor->attachments[i].stencilLoadOp = vkGryphnLoadOperation(info.attachmentInfos[i].stencilLoadOperation);
        renderPass->renderPassDescriptor->attachments[i].stencilStoreOp = vkGryphnStoreOperation(info.attachmentInfos[i].stencilStoreOperation);

        renderPass->renderPassDescriptor->attachments[i].initialLayout = vkGryphnImageLayout(info.attachmentInfos[i].initialLayout);
        renderPass->renderPassDescriptor->attachments[i].finalLayout = vkGryphnImageLayout(info.attachmentInfos[i].finalLayout);
    }

    renderPass->renderPassDescriptor->subpassCount = info.subpassCount;
    renderPass->renderPassDescriptor->subpasses = malloc(sizeof(VkSubpassDescription) * info.subpassCount);
    renderPass->renderPassDescriptor->colorAttachments = malloc(sizeof(VkAttachmentReference*) * info.subpassCount);

    VkAttachmentReference ref = {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    for (int i = 0; i < info.subpassCount; i++) {
        renderPass->renderPassDescriptor->colorAttachments[i] = malloc(sizeof(VkAttachmentReference) * info.subpassInfos[i].colorAttachmentCount);

        for (int c = 0; c < info.subpassInfos[i].colorAttachmentCount; c++) {
            renderPass->renderPassDescriptor->colorAttachments[i][c] = (VkAttachmentReference){
                .attachment = info.subpassInfos[i].colorAttachments[c].index,
                .layout = vkGryphnImageLayout(info.subpassInfos[i].colorAttachments[c].imageLayout)
            };
        }


        renderPass->renderPassDescriptor->subpasses[i] = (VkSubpassDescription){
            .flags = 0,
            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
            .colorAttachmentCount = info.subpassInfos[i].colorAttachmentCount,
            .pColorAttachments = renderPass->renderPassDescriptor->colorAttachments[i]
        };
    }

    renderPass->renderPassDescriptor->dependencies = malloc(sizeof(VkSubpassDependency) * info.dependencyCount);
    for (int i = 0; i < info.dependencyCount; i++) {
        renderPass->renderPassDescriptor->dependencies[i] = (VkSubpassDependency) {
            .srcSubpass = (info.dependencies[i].source == GN_SUBPASS_EXTERNAL) ? VK_SUBPASS_EXTERNAL : info.dependencies[i].source,
            .dstSubpass = (info.dependencies[i].destination == GN_SUBPASS_EXTERNAL) ? VK_SUBPASS_EXTERNAL : info.dependencies[i].destination,
            .srcStageMask = info.dependencies[i].soruceStageMask,
            .srcAccessMask = info.dependencies[i].sourceAccessMask,
            .dstStageMask = info.dependencies[i].destinationStageMask,
            .dstAccessMask = info.dependencies[i].destinationAccessMask
        };
    }

    VkRenderPassCreateInfo renderPassInfo = (VkRenderPassCreateInfo) {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .pNext = NULL,
        .flags = 0,
        .attachmentCount = info.attachmentCount,
        .pAttachments = renderPass->renderPassDescriptor->attachments,
        .subpassCount = info.subpassCount,
        .pSubpasses = renderPass->renderPassDescriptor->subpasses,
        .dependencyCount = info.dependencyCount,
        .pDependencies = renderPass->renderPassDescriptor->dependencies,
    };

    if (vkCreateRenderPass(device->outputDevice->device, &renderPassInfo, NULL, &renderPass->renderPassDescriptor->renderPass) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_RENDER_PASS;

    return GN_SUCCESS;
}


void gnDestroyRenderPassDescriptorFn(gnRenderPassDescriptor renderPass) {
    vkDestroyRenderPass(renderPass->device->outputDevice->device, renderPass->renderPassDescriptor->renderPass, NULL);


    free(renderPass->renderPassDescriptor->attachments);
    free(renderPass->renderPassDescriptor->subpasses);
    free(renderPass->renderPassDescriptor->dependencies);
}
