#pragma once
#include "renderpass/gryphn_render_pass_descriptor.h"
#import <Metal/MTLRenderPass.h>
#import <Metal/Metal.h>

typedef MTLRenderPassDescriptor* mtlSubpass;

typedef struct mtlColorAttachmentCopyInfo {
    MTLPixelFormat format;

    uint32_t attachmentIndex;
    int resolveAttachmentIndex; // -1 means no resolve attachment
} mtlColorAttachmentCopyInfo;

typedef struct mtlSubpassCopyInfo {
    uint32_t colorAttachmentCount;
    mtlColorAttachmentCopyInfo* colorAttachments;
    int depthAttachmentIndex; // -1 means no depth attachment
} mtlSubpassCopyInfo;

typedef struct gnPlatformRenderPassDescriptor_t {
    uint32_t subpassCount;
    mtlSubpass* subpasses;
    mtlSubpassCopyInfo* copyInfos;


} gnPlatformRenderPassDescriptor;

gnReturnCode createMetalRenderPass(gnRenderPassDescriptor renderPass, gnDevice device, gnRenderPassDescriptorInfo info);
void destroyMetalRenderPass(gnRenderPassDescriptor renderPass);
