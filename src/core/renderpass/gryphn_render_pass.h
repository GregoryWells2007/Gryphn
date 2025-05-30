#pragma once
#include "gryphn_render_pass_descriptor.h"
#include "core/framebuffer/gryphn_framebuffer.h"

typedef struct gnRenderPassInfo_t {
    struct gnRenderPassDescriptor_t* renderPassDescriptor;
    struct gnFramebuffer_t* framebuffer;
    gnUInt2 offset;
    gnUInt2 size;
} gnRenderPassInfo;
