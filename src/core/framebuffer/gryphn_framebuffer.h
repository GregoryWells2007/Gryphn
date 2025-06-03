#pragma once
#include "core/renderpass/gryphn_render_pass_descriptor.h"
#include "core/textures/gryphn_texture.h"
#include "utils/math/gryphn_vec2.h"

typedef struct gnFramebufferInfo_t {
    struct gnRenderPassDescriptor_t* renderPassDescriptor;
    uint32_t attachmentCount;
    struct gnTexture_t* attachments;
    gnUInt2 size;
} gnFramebufferInfo;

typedef struct gnFramebuffer_t {
    struct gnPlatformFramebuffer_t* framebuffer;
    struct gnOutputDevice_t* device;
} gnFramebuffer;

gnReturnCode gnCreateFramebuffer(struct gnFramebuffer_t* framebuffer, struct gnOutputDevice_t* device, struct gnFramebufferInfo_t framebufferInfo);
void gnDestroyFramebuffer(struct gnFramebuffer_t* framebuffer);
