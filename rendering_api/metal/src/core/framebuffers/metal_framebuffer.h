#include <core/framebuffers/gryphn_framebuffer.h>
#include <Metal/Metal.hpp>

struct gnPlatformFramebuffer {
    MTL::RenderPassDescriptor* framebuffer;
};

struct gnPlatformFramebufferAttachment {
    MTL::RenderPassAttachmentDescriptor* framebufferAttachment;
};
