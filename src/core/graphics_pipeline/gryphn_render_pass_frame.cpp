#include "gryphn_render_pass_frame.h"

void gnRenderPassFrameSetRenderPass(gnRenderPassFrame& frame, gnRenderPass& renderPass) {
    frame.renderPass = &renderPass;
}
void gnRenderPassFrameSetFramebuffer(gnRenderPassFrame& frame, gnFramebuffer& framebuffer) {
    frame.framebuffer = &framebuffer;
}
void gnRenderPassFrameSetOffset(gnRenderPassFrame& frame, gnUInt2 offset) {
    frame.offset = offset;
}
void gnRenderPassFrameSetRenderArea(gnRenderPassFrame& frame, gnUInt2 area) {
    frame.area = area;
}
void gnRenderPassFrameSetClearColor(gnRenderPassFrame& frame, gnColor& clearColor) {
    frame.clearColor = clearColor;
}
