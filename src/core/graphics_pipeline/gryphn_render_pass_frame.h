#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_render_pass.h"

struct gnPlatformRenderPassFrame;
struct gnFramebuffer;

struct gnRenderPassFrame {
ACCESS_LEVEL:
    gnPlatformRenderPassFrame* renderPassFrame = nullptr;
    gnRenderPass* renderPass;
    gnFramebuffer* framebuffer;
    gnUInt2 offset;
    gnUInt2 area;
    gnColor clearColor;
public:
    gnRenderPassFrame() {}
};

void gnRenderPassFrameSetRenderPass(gnRenderPassFrame& frame, gnRenderPass& renderPass);
void gnRenderPassFrameSetFramebuffer(gnRenderPassFrame& frame, gnFramebuffer& framebuffer);
void gnRenderPassFrameSetOffset(gnRenderPassFrame& frame, gnUInt2 offset);
void gnRenderPassFrameSetRenderArea(gnRenderPassFrame& frame, gnUInt2 area);
void gnRenderPassFrameSetClearColor(gnRenderPassFrame& frame, gnColor& clearColor);
