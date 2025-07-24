#pragma once
#include "framebuffer/gryphn_framebuffer.h"
#include "utils/gryphn_bool.h"
#include "utils/gryphn_image_format.h"
#include "utils/lists/gryphn_array_list.h"
#include "renderpass/metal_render_pass.h"
#import <Metal/Metal.h>
#import <Metal/MTLRenderPass.h>

typedef struct mtlClearCopy {
    gnBool clear;
    MTLRenderPassColorAttachmentDescriptor* descriptor;
} mtlClearCopy;

typedef struct gnPlatformFramebuffer_t {
    uint32_t subpassCount;
    mtlSubpass* subpasses;
    uint32_t* depthAttachmentIndicies;

    uint32_t clearCopyCount;
    mtlClearCopy* clearCopies;
} gnPlatformFramebuffer;

gnBool isDepthFormat(gnImageFormat format);
gnBool isStencilFormat(gnImageFormat format);

gnReturnCode createMetalFramebuffer(gnFramebuffer framebuffer, gnOutputDevice device, gnFramebufferInfo info);
void destroyMetalFramebuffer(gnFramebuffer framebuffer);
