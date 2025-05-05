#include "gryphn_render_pass.h"

void gnRenderPassAddSubpass(gnRenderPass& renderPass, gnSubpass& subpass) {
    gnListAdd(renderPass.subpasses, &subpass);
}

void gnRenderPassSetPresentationQueue(gnRenderPass& renderPass, gnPresentationQueue& presentationQueue) {
    renderPass.presentationQueue = &presentationQueue;
    gnRenderPassSetTarget(renderPass, GN_PRESENTATION_QUEUE);
}

void gnRenderPassSetAttachments(gnRenderPass& renderPass, int count, gnRenderpassAttachment* attachments) {
    renderPass.attachments = attachments;
    renderPass.attachmentCount = count;
}
void gnRenderPassSetTarget(gnRenderPass& renderPass, gnRenderPassTarget target) {
    renderPass.target = target;
}

void gnRenderpassAttachmentSetColorMode(gnRenderpassAttachment& attachment, gnColorMode colorMode) {
    attachment.colorMode = colorMode;
}
