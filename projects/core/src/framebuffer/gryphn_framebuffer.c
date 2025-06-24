#include "gryphn_framebuffer.h"
#include "stdlib.h"
#include "output_device/gryphn_output_device.h"

gnReturnCode gnCreateFramebuffer(gnFramebuffer* framebuffer, gnOutputDeviceHandle device, gnFramebufferInfo framebufferInfo) {
    *framebuffer = malloc(sizeof(struct gnFramebuffer_t));
    (*framebuffer)->device = device;
    return device->deviceFunctions->_gnCreateFramebuffer(*framebuffer, device, framebufferInfo);
}

void gnDestroyFramebuffer(gnFramebuffer framebuffer) {
    framebuffer->device->deviceFunctions->_gnDestroyFramebuffer(framebuffer);
}
