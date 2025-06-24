#pragma once
#include "framebuffer/gryphn_framebuffer.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformFramebuffer_t {
    VkFramebuffer framebuffer;
} gnPlatformFramebuffer;

gnReturnCode createFramebuffer(gnFramebuffer framebuffer, gnDevice device, gnFramebufferInfo info);
void destroyFramebuffer(gnFramebuffer framebuffer);
