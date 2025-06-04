#include "gryphn_render_pass_descriptor.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreateRenderPassDescriptor(gnRenderPassDescriptorHandle* renderPass, gnOutputDeviceHandle device, struct gnRenderPassDescriptorInfo_t info) {
    *renderPass = malloc(sizeof(struct gnRenderPassDescriptor_t));

    (*renderPass)->device = device;
    (*renderPass)->info = info;
    return device->deviceFunctions->_gnCreateRenderPassDescriptor(*renderPass, device, info);
}

void gnDestroyRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass) {
    renderPass->device->deviceFunctions->_gnDestroyRenderPassDescriptor(renderPass);
}
