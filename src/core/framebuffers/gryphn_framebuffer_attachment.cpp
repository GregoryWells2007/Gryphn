#include "gryphn_framebuffer_attachment.h"

void gnFramebufferAttachmentSetSize(gnFramebufferAttachment& framebuffer, gnUInt2 newSize) {
    framebuffer.size = newSize;
}

void gnFramebufferAttachmentSetColorMode(gnFramebufferAttachment& framebuffer, gnColorMode newColorMode) {
    framebuffer.colorMode = newColorMode;
}

void gnFramebufferAttachmentBindTexture(gnFramebufferAttachment& framebuffer, gnTexture* texture) {
    framebuffer.texture = texture;
}

void gnFramebufferAttachmentSetBindPoint(gnFramebufferAttachment& framebuffer, gnFramebufferAttachmentBindPoint bindPoint) {
    framebuffer.bindPoint = bindPoint;
}
