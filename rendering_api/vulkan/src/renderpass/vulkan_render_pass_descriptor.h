#pragma once
#include "core/renderpass/gryphn_render_pass_descriptor.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformRenderPassDescriptor_t {
    VkRenderPass renderPass;

    uint32_t attachmentCount;
    VkAttachmentDescription* attachments;

    uint32_t subpassCount;
    VkSubpassDescription* subpasses;
    VkSubpassDependency* dependencies;

    VkAttachmentReference** colorAttachments;
} gnPlatformRenderPassDescriptor;
