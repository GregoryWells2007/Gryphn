#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/presentation_queue/gryphn_presentation_queue.h"
#include <core/textures/gryphn_texture.h>

struct gnPlatformFramebufferAttachment;
struct gnFramebuffer;

enum gnFramebufferAttachmentBindPoint {
    GN_COLOR_ATTACHMENT, GN_DEPTH_ATTACHMENT, GN_STENCIL_ATTACHMENT, GN_DEPTH_STENCIL_ATTACHMENT
};

struct gnFramebufferAttachment {
ACCESS_LEVEL:
    gnPlatformFramebufferAttachment* framebufferAttachment = nullptr;

    gnUInt2 size;
    gnColorMode colorMode;
    gnFramebufferAttachmentBindPoint bindPoint = GN_COLOR_ATTACHMENT;
    gnTexture* texture;
    gnFramebuffer* framebuffer;
public:
    gnFramebufferAttachment() {}
};

void gnFramebufferAttachmentSetSize(gnFramebufferAttachment& framebuffer, gnUInt2 newSize);
void gnFramebufferAttachmentSetColorMode(gnFramebufferAttachment& framebuffer, gnColorMode newColorMode);
void gnFramebufferAttachmentSetBindPoint(gnFramebufferAttachment& framebuffer, gnFramebufferAttachmentBindPoint bindPoint);
void gnFramebufferAttachmentBindTexture(gnFramebufferAttachment& framebuffer, gnTexture* texture);

inline gnReturnCode (*gnCreateFramebufferAttachment)(gnFramebufferAttachment* attachment, gnPresentationQueue& queue);
