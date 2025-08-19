#pragma once
#include "glad/glad.h"
#include "core/src/framebuffer/gryphn_framebuffer.h"

typedef struct gnPlatformFramebuffer_t {
    uint32_t framebufferCount;
    GLuint* framebuffers;
} gnPlatformFramebuffer_t;

gnReturnCode openglCreateFramebuffer(gnFramebuffer framebuffer, gnDevice device, gnFramebufferInfo info);
void openglDestroyFramebuffer(gnFramebuffer framebuffer);
