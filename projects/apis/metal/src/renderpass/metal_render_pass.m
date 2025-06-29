#include "metal_render_pass.h"

gnReturnCode createMetalRenderPass(gnRenderPassDescriptor renderPass, gnDevice device, gnRenderPassDescriptorInfo info) {
    renderPass->renderPassDescriptor = malloc(sizeof(gnPlatformRenderPassDescriptor));
    renderPass->renderPassDescriptor->passDescriptor = [[MTLRenderPassDescriptor alloc] init];

    return GN_SUCCESS;
}

void destroyMetalRenderPass(gnRenderPassDescriptor renderPass) {
    [renderPass->renderPassDescriptor->passDescriptor release];
    free(renderPass->renderPassDescriptor);
}
