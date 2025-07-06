#pragma once
#include "framebuffer/gryphn_framebuffer.h"
#include "utils/gryphn_bool.h"
#include "utils/gryphn_image_format.h"
#include "utils/lists/gryphn_array_list.h"
#import <Metal/Metal.h>
#import <Metal/MTLRenderPass.h>

typedef MTLRenderPassDescriptor* mtlSubpass;

typedef struct gnPlatformFramebuffer_t {
    uint32_t subpassCount;
    mtlSubpass* subpasses;
} gnPlatformFramebuffer;

gnBool isDepthFormat(gnImageFormat format);
gnBool isStencilFormat(gnImageFormat format);

gnReturnCode createMetalFramebuffer(gnFramebuffer framebuffer, gnOutputDevice device, gnFramebufferInfo info);
void destroyMetalFramebuffer(gnFramebuffer framebuffer);
