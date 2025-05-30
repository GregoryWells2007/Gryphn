#include "vulkan_render_pass_descriptor.h"
#include "vulkan_surface/vulkan_surface.h"
#include "output_device/vulkan_output_devices.h"

VkAttachmentLoadOp vkGryphnLoadOperation(enum gnLoadOperation_e loadOperation) {
    switch(loadOperation) {
    case GN_LOAD_OPERATION_LOAD: return VK_ATTACHMENT_LOAD_OP_LOAD;
    case GN_LOAD_OPERATION_CLEAR: return VK_ATTACHMENT_LOAD_OP_CLEAR;
    case GN_LOAD_OPERATION_DONT_CARE: return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    }
}

VkAttachmentStoreOp vkGryphnStoreOperation(enum gnStoreOperation_e storeOperation) {
    switch (storeOperation) {
    case GN_STORE_OPERATION_STORE: return VK_ATTACHMENT_STORE_OP_STORE;
    case GN_STORE_OPERATION_DONT_CARE: return VK_ATTACHMENT_STORE_OP_DONT_CARE;
    }
}

VkImageLayout vkGryphnImageLayout(enum gnImageLayout_e layout) {
    switch(layout) {
    case GN_LAYOUT_UNDEFINED: return VK_IMAGE_LAYOUT_UNDEFINED;
    case GN_LAYOUT_PRESENTATION_QUEUE_IMAGE: return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    case GN_LAYOUT_TRANSFER_DESTINATION: return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    case GN_COLOR_ATTACHMENT: return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
}

gnReturnCode gnCreateRenderPassDescriptorFn(struct gnRenderPassDescriptor_t* renderPass, struct gnOutputDevice_t* device, struct gnRenderPassDescriptorInfo_t info) {
    renderPass->renderPassDescriptor = malloc(sizeof(gnPlatformRenderPassDescriptor));

    VkAttachmentDescription* attachments = malloc(sizeof(VkAttachmentDescription) * info.attachmentCount);
    for (int i = 0; i < info.attachmentCount; i++) {
        attachments[i].format = vkGryphnFormatToVulkanFormat(info.attachmentInfos[i].format);
        attachments[i].samples = VK_SAMPLE_COUNT_1_BIT;

        attachments[i].loadOp = vkGryphnLoadOperation(info.attachmentInfos[i].loadOperation);
        attachments[i].storeOp = vkGryphnStoreOperation(info.attachmentInfos[i].storeOperation);

        attachments[i].stencilLoadOp = vkGryphnLoadOperation(info.attachmentInfos[i].stencilLoadOperation);
        attachments[i].stencilStoreOp = vkGryphnStoreOperation(info.attachmentInfos[i].stencilStoreOperation);

        attachments[i].initialLayout = vkGryphnImageLayout(info.attachmentInfos[i].initialLayout);
        attachments[i].finalLayout = vkGryphnImageLayout(info.attachmentInfos[i].finalLayout);
    }

    VkSubpassDescription* subpasses = malloc(sizeof(VkSubpassDescription) * info.subpassCount);

    for (int i = 0; i < info.subpassCount; i++) {
        subpasses[i].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpasses[i].colorAttachmentCount = info.subpassInfos[i].colorAttachmentCount;
        VkAttachmentReference* colorAttachments = malloc(sizeof(VkAttachmentReference) * info.subpassInfos[i].colorAttachmentCount);
        for (int c = 0; c < info.subpassInfos[i].colorAttachmentCount; c++) {
            colorAttachments[c].attachment = info.subpassInfos[i].colorAttachments[c].index;
            colorAttachments[c].layout = vkGryphnImageLayout(info.subpassInfos[i].colorAttachments[c].imageLayout);
        }
        subpasses[i].pColorAttachments = colorAttachments;
    }

    VkSubpassDependency* dependencies = malloc(sizeof(VkSubpassDependency) * info.dependencyCount);
    for (int i = 0; i < info.dependencyCount; i++) {
        dependencies[i] = (VkSubpassDependency) {
            .srcSubpass = (info.dependencies[i].source == GN_SUBPASS_EXTERNAL) ? VK_SUBPASS_EXTERNAL : info.dependencies[i].source,
            .dstSubpass = (info.dependencies[i].destination == GN_SUBPASS_EXTERNAL) ? VK_SUBPASS_EXTERNAL : info.dependencies[i].destination,
            .srcStageMask = info.dependencies[i].soruceStageMask,
            .srcAccessMask = info.dependencies[i].sourceAccessMask,
            .dstStageMask = info.dependencies[i].destinationStageMask,
            .dstAccessMask = info.dependencies[i].destinationAccessMask
        };
    }

    VkRenderPassCreateInfo renderPassInfo = (VkRenderPassCreateInfo){
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = info.attachmentCount,
        .pAttachments = attachments,
        .subpassCount = info.subpassCount,
        .pSubpasses = subpasses,
        .dependencyCount = info.dependencyCount,
        .pDependencies = dependencies
    };

    if (vkCreateRenderPass(device->outputDevice->device, &renderPassInfo, NULL, &renderPass->renderPassDescriptor->renderPass) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_RENDER_PASS;
    }

    free(attachments);
    free(subpasses);

    return GN_SUCCESS;
}


void gnDestroyRenderPassDescriptorFn(struct gnRenderPassDescriptor_t* renderPass) {
    vkDestroyRenderPass(renderPass->device->outputDevice->device, renderPass->renderPassDescriptor->renderPass, NULL);
}
