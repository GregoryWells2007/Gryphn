#include "core/framebuffers/gryphn_framebuffer.h"
#include <vulkan/vulkan.h>
#include "../output_device/vulkan_output_devices.h"
#include "../presentation_queue/vulkan_presentation_queue.h"
#include "../graphics_pipeline/vulkan_renderpass.h"
#include "vulkan_framebuffer.h"
#include "../textures/vulkan_texture.h"

GN_EXPORT gnReturnCode gnCreateFramebufferFn(gnFramebuffer* framebuffer, const gnRenderPass& renderpass) {
    if (framebuffer->framebuffer == nullptr) framebuffer->framebuffer = new gnPlatformFramebuffer();
    std::vector<VkImageView> attachments = {};

    for (int i = 0; i < gnListLength(framebuffer->framebufferAttachments); i++) {
        if (framebuffer->framebufferAttachments[i].texture->texture == nullptr) framebuffer->framebufferAttachments[i].texture->texture = new gnPlatformTexture();
        framebuffer->framebufferAttachments[i].texture->texture->outputDevice = renderpass.renderpass->outputDevice;
        attachments.push_back(framebuffer->framebufferAttachments[i].texture->texture->textureImageView);
    };

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderpass.renderpass->renderPass;
    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = framebuffer->size.x;
    framebufferInfo.height = framebuffer->size.y;
    framebufferInfo.layers = 1;

    // framebuffer->framebuffer->pipeline = const_cast<gnGraphicsPipeline*>(&pipeline);
    framebuffer->framebuffer->outputDevice = renderpass.renderpass->outputDevice;


    if (vkCreateFramebuffer(renderpass.renderpass->outputDevice->outputDevice->device, &framebufferInfo, nullptr, &framebuffer->framebuffer->framebuffer) != VK_SUCCESS) {
        GN_RETURN_ERROR("Failed to create framebuffer");
    }

    return GN_SUCCESS;
}

GN_EXPORT gnReturnCode gnCreateFramebufferAttachmentFn(gnFramebufferAttachment* attachment, gnPresentationQueue& queue) {
    if (attachment->framebufferAttachment == nullptr) attachment->framebufferAttachment = new gnPlatformFramebufferAttachment();
    if (attachment->colorMode == GN_RGBA8) {
        attachment->framebufferAttachment->attachment.format = queue.presentationQueue->swapchainDetails.surfaceFormat.format;
        attachment->framebufferAttachment->attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        attachment->framebufferAttachment->attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachment->framebufferAttachment->attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachment->framebufferAttachment->attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachment->framebufferAttachment->attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachment->framebufferAttachment->attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        attachment->framebufferAttachment->attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        attachment->framebufferAttachment->attachmentRef.attachment = 0;
        attachment->framebufferAttachment->attachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    } else if (attachment->colorMode == GN_DEPTH_STENCIL) {
        VkFormat format;
        gnReturnCode depthFormatReturnError = findDepthFormat(*queue.presentationQueue->outputDevice, format);
        if (depthFormatReturnError != GN_SUCCESS) return depthFormatReturnError;

        attachment->framebufferAttachment->attachment.format = format;
        attachment->framebufferAttachment->attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        attachment->framebufferAttachment->attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachment->framebufferAttachment->attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachment->framebufferAttachment->attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachment->framebufferAttachment->attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachment->framebufferAttachment->attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        attachment->framebufferAttachment->attachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    }


    return GN_SUCCESS;
}

// texture

GN_EXPORT void gnDestroyFramebufferFn(const gnFramebuffer& framebuffer) {
    vkDestroyFramebuffer(framebuffer.framebuffer->outputDevice->outputDevice->device, framebuffer.framebuffer->framebuffer, nullptr);
}
