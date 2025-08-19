#include "opengl_framebuffer.h"
#include "stdlib.h"
#include "renderpass/opengl_render_pass_descriptor.h"
#include "textures/opengl_texture.h"
#include "stdio.h"
#include "core/src/output_device/gryphn_output_device.h"
#include "core/src/instance/gryphn_instance.h"

gnReturnCode openglCreateFramebuffer(gnFramebuffer framebuffer, gnDevice device, gnFramebufferInfo info) {
    framebuffer->framebuffer = malloc(sizeof(struct gnPlatformFramebuffer_t));
    framebuffer->framebuffer->framebufferCount = info.renderPassDescriptor->renderPassDescriptor->subpassCount;
    framebuffer->framebuffer->framebuffers = malloc(sizeof(GLuint) * info.renderPassDescriptor->renderPassDescriptor->subpassCount);
    for (int i = 0; i < info.renderPassDescriptor->renderPassDescriptor->subpassCount; i++) {
        glCreateFramebuffers(1, &framebuffer->framebuffer->framebuffers[i]);
        for (int c = 0; c < info.renderPassDescriptor->renderPassDescriptor->subpasses[i].colorAttachmentCount; c++)
            glNamedFramebufferTexture(framebuffer->framebuffer->framebuffers[i], GL_COLOR_ATTACHMENT0 + c, info.attachments[info.renderPassDescriptor->renderPassDescriptor->subpasses[i].colorAttachments[c].attachmentIndex]->texture->id, 0);
        if (info.renderPassDescriptor->renderPassDescriptor->subpasses[i].depthAttachment.index >= 0)
            glNamedFramebufferTexture(framebuffer->framebuffer->framebuffers[i], GL_DEPTH_STENCIL_ATTACHMENT, info.attachments[info.renderPassDescriptor->renderPassDescriptor->subpasses[i].depthAttachment.index]->texture->id, 0);
        if (glCheckNamedFramebufferStatus(framebuffer->framebuffer->framebuffers[i], GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            char string[500];
            snprintf(string, 500, "Failed to create OpenGL framebuffer: 0x%x\n", glCheckNamedFramebufferStatus(framebuffer->framebuffer->framebuffers[i], GL_FRAMEBUFFER));
            gnDebuggerSetErrorMessage(framebuffer->device->instance->debugger, (gnMessageData){
                .message = gnCreateString(string)
            });
            return GN_FAILED_CREATE_OBJECT;
        }
    }
    return GN_SUCCESS;
}
void openglDestroyFramebuffer(gnFramebuffer framebuffer) {
    for (int i = 0; i < framebuffer->framebuffer->framebufferCount; i++)
        glDeleteFramebuffers(1, &framebuffer->framebuffer->framebuffers[i]);
    free(framebuffer->framebuffer);
}
