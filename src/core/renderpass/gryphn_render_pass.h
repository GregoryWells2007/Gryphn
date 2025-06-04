#pragma once
#include "core/framebuffer/gryphn_framebuffer.h"
#include "utils/types/gryphn_color.h"

typedef struct gnRenderPassInfo_t {
    gnRenderPassDescriptorHandle renderPassDescriptor;
    struct gnFramebuffer_t* framebuffer;
    gnUInt2 offset;
    gnUInt2 size;
    uint32_t clearValueCount;
    gnClearValue* clearValues;
} gnRenderPassInfo;
