#include "gryphn_render_pass_descriptor.h"
#include "output_device/gryphn_output_device.h"

gnReturnCode gnCreateRenderPassDescriptor(gnRenderPassDescriptorHandle* renderPass, gnOutputDeviceHandle device, gnRenderPassDescriptorInfo info) {
    *renderPass = malloc(sizeof(struct gnRenderPassDescriptor_t));
    (*renderPass)->device = device;
    (*renderPass)->info = info;
    return device->deviceFunctions->_gnCreateRenderPassDescriptor(*renderPass, device, info);
}

void gnDestroyRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass) {
    renderPass->device->deviceFunctions->_gnDestroyRenderPassDescriptor(renderPass);
}
