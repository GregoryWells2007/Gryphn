#pragma once
#include <gryphn/gryphn_utils.h>
#include <core/textures/gryphn_texture.h>

struct gnPlatformRenderpassAttachment;

struct gnRenderpassAttachment {
ACCESS_LEVEL:
    gnPlatformRenderpassAttachment* renderpassAttachment = nullptr;
    gnColorMode colorMode;
public:
    gnRenderpassAttachment() {}
};

void gnRenderpassAttachmentSetColorMode(gnRenderpassAttachment& attachment, gnColorMode colorMode);
