#include "metal_render_pass.h"

gnReturnCode gnCreateRenderPassDescriptorFn(gnRenderPassDescriptor renderPass, gnOutputDevice device, gnRenderPassDescriptorInfo info) {
    renderPass->renderPassDescriptor = malloc(sizeof(gnPlatformRenderPassDescriptor));
    renderPass->renderPassDescriptor->passDescriptor = [[MTLRenderPassDescriptor alloc] init];

    return GN_SUCCESS;
}

void gnDestroyRenderPassDescriptorFn(struct gnRenderPassDescriptor_t* renderPass) {
    [renderPass->renderPassDescriptor->passDescriptor release];
    free(renderPass->renderPassDescriptor);
}
