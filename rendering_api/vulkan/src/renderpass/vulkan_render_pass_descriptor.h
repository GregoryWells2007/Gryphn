#pragma once
#include "core/renderpass/gryphn_render_pass_descriptor.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformRenderPassDescriptor_t {
    VkRenderPass renderPass;
} gnPlatformRenderPassDescriptor;
