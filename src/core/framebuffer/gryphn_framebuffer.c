#include "gryphn_framebuffer.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreateFramebuffer(gnFramebuffer* framebuffer, gnOutputDeviceHandle device, gnFramebufferInfo framebufferInfo) {
    *framebuffer = malloc(sizeof(struct gnFramebuffer_t));
    (*framebuffer)->device = device;
    return device->deviceFunctions->_gnCreateFramebuffer(*framebuffer, device, framebufferInfo);
}

void gnDestroyFramebuffer(gnFramebuffer framebuffer) {
    framebuffer->device->deviceFunctions->_gnDestroyFramebuffer(framebuffer);
}
