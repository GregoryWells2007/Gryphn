#pragma once
#include "framebuffer/gryphn_framebuffer.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformFramebuffer_t {
    VkFramebuffer framebuffer;
} gnPlatformFramebuffer;
