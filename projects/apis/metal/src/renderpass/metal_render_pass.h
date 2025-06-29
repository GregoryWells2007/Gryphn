#pragma once
#include "renderpass/gryphn_render_pass_descriptor.h"
#import <Metal/MTLRenderPass.h>

typedef struct gnPlatformRenderPassDescriptor_t {
    MTLRenderPassDescriptor* passDescriptor;
} gnPlatformRenderPassDescriptor;

gnReturnCode createMetalRenderPass(gnRenderPassDescriptor renderPass, gnDevice device, gnRenderPassDescriptorInfo info);
void destroyMetalRenderPass(gnRenderPassDescriptor renderPass);
