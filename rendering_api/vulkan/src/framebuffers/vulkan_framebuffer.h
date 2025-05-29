#pragma once
#include "core/framebuffer/gryphn_framebuffer.h"
#include <vulkan/vulkan.h>

typedef struct gnPlatformFramebuffer_t {
    VkFramebuffer framebuffer;
} gnPlatformFramebuffer;
