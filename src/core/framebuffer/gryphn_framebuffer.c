#include "gryphn_framebuffer.h"

gnReturnCode gnCreateFramebuffer(struct gnFramebuffer_t* framebuffer, struct gnOutputDevice_t* device, struct gnFramebufferInfo_t framebufferInfo) {
    framebuffer->device = device;
}

void gnDestroyFramebuffer(struct gnFramebuffer_t *framebuffer) {

}
