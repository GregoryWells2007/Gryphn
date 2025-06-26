#include "gryphn_framebuffer.h"
#include "stdlib.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnCreateFramebuffer(gnFramebuffer* framebuffer, gnOutputDeviceHandle device, gnFramebufferInfo framebufferInfo) {
    *framebuffer = malloc(sizeof(struct gnFramebuffer_t));
    (*framebuffer)->device = device;
    return device->instance->callingLayer->deviceFunctions._gnCreateFramebuffer(*framebuffer, device, framebufferInfo);
}

void gnDestroyFramebuffer(gnFramebuffer framebuffer) {
    framebuffer->device->instance->callingLayer->deviceFunctions._gnDestroyFramebuffer(framebuffer);
}
