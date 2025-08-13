#pragma once
#include "core/src/renderpass/gryphn_render_pass_descriptor.h"

typedef struct gnPlatformRenderPassDescriptor_t gnPlatformRenderPassDescriptor;
gnReturnCode openglCreateRenderPass(gnRenderPassDescriptor renderPass, gnDevice device, gnRenderPassDescriptorInfo info);
void openglDestroyRenderPass(gnRenderPassDescriptor renderPass);
