#pragma once
#include "glad/glad.h"
#include "core/src/renderpass/gryphn_render_pass_descriptor.h"
#include "utils/gryphn_color.h"

typedef struct glColorAttachment {
    gnColor clearColor;
    gnLoadOperation loadOperation;
    gnStoreOperation storeOperation;

    GLint format;
    uint32_t attachmentIndex;
    int resolveAttachmentIndex; // -1 = no attachment
} glColorAttachment;

typedef struct gnDepthAttachment {
    int index;
    gnLoadOperation loadOperation;
    gnStoreOperation storeOperation;
    GLint format;
} gnDepthAttachment;

typedef struct glSubpass {
    uint32_t colorAttachmentCount;
    glColorAttachment* colorAttachments;
    gnDepthAttachment depthAttachment;
} glSubpass;

typedef struct gnPlatformRenderPassDescriptor_t {
    uint32_t subpassCount;
    glSubpass* subpasses;
} gnPlatformRenderPassDescriptor;
gnReturnCode openglCreateRenderPass(gnRenderPassDescriptor renderPass, gnDevice device, gnRenderPassDescriptorInfo info);
void openglDestroyRenderPass(gnRenderPassDescriptor renderPass);
