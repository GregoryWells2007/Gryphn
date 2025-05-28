#include "gryphn_render_pass_descriptor.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreateRenderPassDescriptor(struct gnRenderPassDescriptor_t* renderPass, struct gnOutputDevice_t* device, struct gnRenderPassDescriptorInfo_t info) {
    renderPass->device = device;
    return device->deviceFunctions->_gnCreateRenderPassDescriptor(renderPass, device, info);
}

void gnDestroyRenderPassDescriptor(struct gnRenderPassDescriptor_t* renderPass) {
    renderPass->device->deviceFunctions->_gnDestroyRenderPassDescriptor(renderPass);
}
