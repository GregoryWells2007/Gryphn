#pragma once
#include "renderpass/gryphn_render_pass_descriptor.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformRenderPassDescriptor_t {
    VkRenderPass renderPass;

    uint32_t attachmentCount;
    VkAttachmentDescription* attachments;

    uint32_t subpassCount;
    VkSubpassDescription* subpasses;
    VkSubpassDependency* dependencies;

    VkAttachmentReference** colorAttachments;
    VkAttachmentReference* depthAttachments;
} gnPlatformRenderPassDescriptor;

VkPipelineStageFlags vkGryphnRenderPassStage(gnRenderPassStage stage);

gnReturnCode createRenderPass(gnRenderPassDescriptor renderPass, gnDevice device, gnRenderPassDescriptorInfo info);
void destroyRenderPass(gnRenderPassDescriptor renderPass);
