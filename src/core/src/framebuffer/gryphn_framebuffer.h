#pragma once
#include "utils/math/gryphn_vec2.h"
#include "utils/gryphn_error_code.h"
#include "gryphn_handles.h"

typedef struct gnFramebufferInfo_t {
    gnRenderPassDescriptorHandle renderPassDescriptor;
    uint32_t attachmentCount;
    gnTextureHandle* attachments;
    gnUInt2 size;
} gnFramebufferInfo;

#ifdef GN_REVEAL_IMPL
struct gnFramebuffer_t {
    struct gnPlatformFramebuffer_t* framebuffer;
    gnOutputDeviceHandle device;
};
#endif

gnReturnCode gnCreateFramebuffer(gnFramebuffer* framebuffer, gnOutputDeviceHandle device, gnFramebufferInfo framebufferInfo);
void gnDestroyFramebuffer(gnFramebuffer framebuffer);
