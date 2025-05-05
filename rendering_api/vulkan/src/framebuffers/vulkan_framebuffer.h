#pragma once
#include <vulkan/vulkan.h>
#include "core/graphics_pipeline/gryphn_graphics_pipeline.h"
#include <core/framebuffers/gryphn_framebuffer.h>

struct gnPlatformFramebuffer {
    VkFramebuffer framebuffer;
    gnRenderPass* renderpass;
    gnOutputDevice* outputDevice;
};

struct gnPlatformFramebufferAttachment {
    VkAttachmentDescription attachment{};
    VkAttachmentReference attachmentRef{};
};
