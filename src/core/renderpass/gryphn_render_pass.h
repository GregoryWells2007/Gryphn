#pragma once
#include "utils/gryphn_color.h"
#include "utils/math/gryphn_vec2.h"
#include "core/gryphn_handles.h"

typedef struct gnRenderPassInfo_t {
    gnRenderPassDescriptorHandle renderPassDescriptor;
    gnFramebuffer framebuffer;
    gnUInt2 offset;
    gnUInt2 size;
    uint32_t clearValueCount;
    gnClearValue* clearValues;
} gnRenderPassInfo;
