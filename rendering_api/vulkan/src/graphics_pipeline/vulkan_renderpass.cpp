#include "vulkan_renderpass.h"
#include "core/graphics_pipeline/gryphn_render_pass.h"
#include "core/output_device/gryphn_output_device.h"
#include <vulkan/vulkan.h>
#include "vector"
#include "../textures/vulkan_texture.h"
#include "../presentation_queue/vulkan_presentation_queue.h"

struct gnPlatformRenderpassAttachment {
    VkAttachmentDescription attachment{};
    VkAttachmentReference attachmentRef{};
};

void vulkanCreateSubpass(gnSubpass* subpass) {
    if (subpass->subpass == nullptr) subpass->subpass = new gnPlatformSubpass();

    subpass->subpass->subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    subpass->subpass->dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    subpass->subpass->dependency.dstSubpass = 0;

    subpass->subpass->dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpass->subpass->dependency.srcAccessMask = 0;

    subpass->subpass->dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpass->subpass->dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

}

void vulkanCreateRenderpass(gnRenderPass* renderpass) {
    if (renderpass->renderpass == nullptr) renderpass->renderpass = new gnPlatformRenderPass();
}

GN_EXPORT gnReturnCode gnCreateRenderPassFn(gnRenderPass* renderPass, const gnOutputDevice& device) {
    vulkanCreateRenderpass(renderPass);
    renderPass->renderpass->outputDevice = const_cast<gnOutputDevice*>(&device);

    std::vector<VkAttachmentDescription> attachments;
    std::vector<VkAttachmentReference> attachmentRefs;

    for (int i = 0; i < renderPass->attachmentCount; i++) {
        VkAttachmentDescription attachment{};
        attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;


        // attachment->renderpassAttachment->attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        // attachment->renderpassAttachment->attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        // attachment->renderpassAttachment->attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        // attachment->renderpassAttachment->attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        // attachment->renderpassAttachment->attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        // attachment->renderpassAttachment->attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        // attachment->renderpassAttachment->attachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = i;

        if (renderPass->presentationQueue == nullptr) {
            GN_RETURN_ERROR("the presentation queue has not been set");
        }

        if (renderPass->attachments[i].colorMode == GN_RGBA8) {
            attachment.format = renderPass->presentationQueue->presentationQueue->swapchainDetails.surfaceFormat.format;
            attachment.finalLayout = (renderPass->target == GN_SHADER_READ) ? VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL : VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        } else if (renderPass->attachments[i].colorMode == GN_DEPTH_STENCIL) {
            VkFormat format;
            findDepthFormat(device, format);

            attachment.format = format;
            attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            colorAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        }

        attachments.push_back(attachment);
        attachmentRefs.push_back(colorAttachmentRef);
    }

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &attachmentRefs[0];
    subpass.pDepthStencilAttachment = &attachmentRefs[1];

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(device.outputDevice->device, &renderPassInfo, nullptr, &renderPass->renderpass->renderPass) != VK_SUCCESS) {
        return GN_FAILED;
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyRenderPassFn(gnRenderPass& renderPass) {
    vkDestroyRenderPass(renderPass.renderpass->outputDevice->outputDevice->device, renderPass.renderpass->renderPass, nullptr);
}
