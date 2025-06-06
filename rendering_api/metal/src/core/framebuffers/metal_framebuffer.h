#pragma once
#include "core/framebuffer/gryphn_framebuffer.h"
#include "utils/gryphn_bool.h"
#include "utils/gryphn_image_format.h"
#import <Metal/Metal.h>
#import <Metal/MTLRenderPass.h>

typedef struct gnPlatformFramebuffer_t {
    MTLRenderPassDescriptor* framebuffer;
} gnPlatformFramebuffer;

gnBool isDepthFormat(gnImageFormat format);
gnBool isStencilFormat(gnImageFormat format);
