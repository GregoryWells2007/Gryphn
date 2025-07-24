#include "gryphn_render_pass_descriptor.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

#include "stdio.h"

gnReturnCode gnCreateRenderPassDescriptor(gnRenderPassDescriptorHandle* renderPass, gnOutputDeviceHandle device, gnRenderPassDescriptorInfo info) {
    *renderPass = malloc(sizeof(struct gnRenderPassDescriptor_t));
    (*renderPass)->device = device;

    return device->instance->callingLayer->deviceFunctions._gnCreateRenderPassDescriptor(*renderPass, device, info);
}

void gnDestroyRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass) {
    renderPass->device->instance->callingLayer->deviceFunctions._gnDestroyRenderPassDescriptor(renderPass);
}
