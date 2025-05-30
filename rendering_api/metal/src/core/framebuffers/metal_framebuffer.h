#pragma once
#include "core/framebuffer/gryphn_framebuffer.h"
#import <Metal/Metal.h>
#import <Metal/MTLRenderPass.h>

typedef struct gnPlatformFramebuffer_t {
    MTLRenderPassDescriptor* framebuffer;
} gnPlatformFramebuffer;

gnBool isDepthFormat(gnImageFormat format);
gnBool isStencilFormat(gnImageFormat format);
