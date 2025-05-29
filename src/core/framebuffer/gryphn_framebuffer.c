#include "gryphn_framebuffer.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreateFramebuffer(struct gnFramebuffer_t* framebuffer, struct gnOutputDevice_t* device, struct gnFramebufferInfo_t framebufferInfo) {
    framebuffer->device = device;
    return device->deviceFunctions->_gnCreateFramebuffer(framebuffer, device, framebufferInfo);
}

void gnDestroyFramebuffer(struct gnFramebuffer_t *framebuffer) {
    framebuffer->device->deviceFunctions->_gnDestroyFramebuffer(framebuffer);
}
