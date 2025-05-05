#pragma once
#include "gryphn_framebuffer_attachment.h"
#include <core/graphics_pipeline/gryphn_render_pass.h>

struct gnPlatformFramebuffer;
struct gnGraphicsPipeline;

struct gnFramebuffer {
ACCESS_LEVEL:
    gnPlatformFramebuffer* framebuffer = nullptr;

    gnList<gnFramebufferAttachment> framebufferAttachments = gnCreateList<gnFramebufferAttachment>(0);
    gnPresentationQueue* queue;
    gnUInt2 size;
public:
    gnFramebuffer() {}
};

void gnFramebufferBindAtachment(gnFramebuffer& framebuffer, int index, gnFramebufferAttachment& attachment);
void gnFramebufferBindPresentationQueue(gnFramebuffer& framebuffer, gnPresentationQueue& queue);
void gnFramebufferSetSize(gnFramebuffer& framebuffer, gnUInt2 size);

inline gnReturnCode (*gnCreateFramebuffer)(gnFramebuffer* framebuffer, const gnRenderPass& pipeline);
inline void (*gnDestroyFramebuffer)(const gnFramebuffer& framebuffer);
