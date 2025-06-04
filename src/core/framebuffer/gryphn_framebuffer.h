#pragma once
#include "utils/math/gryphn_vec2.h"
#include "utils/gryphn_error_code.h"
#include "core/gryphn_handles.h"

typedef struct gnFramebufferInfo_t {
    gnRenderPassDescriptorHandle renderPassDescriptor;
    uint32_t attachmentCount;
    gnTextureHandle* attachments;
    gnUInt2 size;
} gnFramebufferInfo;

typedef struct gnFramebuffer_t {
    struct gnPlatformFramebuffer_t* framebuffer;
    gnOutputDeviceHandle device;
} gnFramebuffer;

gnReturnCode gnCreateFramebuffer(struct gnFramebuffer_t* framebuffer, gnOutputDeviceHandle device, struct gnFramebufferInfo_t framebufferInfo);
void gnDestroyFramebuffer(struct gnFramebuffer_t* framebuffer);
