#include "gryphn_framebuffer.h"

void gnFramebufferBindAtachment(gnFramebuffer& framebuffer, int index, gnFramebufferAttachment& attachment) {
    if (index < gnListLength(framebuffer.framebufferAttachments)) {
        gnListSet(framebuffer.framebufferAttachments, index, attachment);
    } else {
        gnListAdd(framebuffer.framebufferAttachments, attachment);
    }
    attachment.framebuffer = const_cast<gnFramebuffer*>(&framebuffer);
}

void gnFramebufferBindPresentationQueue(gnFramebuffer& framebuffer, gnPresentationQueue& queue) {
    framebuffer.queue = &queue;
}

void gnFramebufferSetSize(gnFramebuffer& framebuffer, gnUInt2 size) {
    framebuffer.size = {size.x, size.y};
}
