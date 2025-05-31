#include "core/present/gryphn_present.h"
#include "core/instance/metal_instance.h"
#include "core/surface/metal_surface.h"
#include "core/devices/metal_output_devices.h"
#include "core/sync/semaphore/metal_semaphore.h"
#include "core/presentation_queue/metal_presentation_queue.h"
#include "core/debugger/gryphn_debugger.h"
#import <QuartzCore/CAMetalLayer.h>

gnReturnCode gnPresentFn(struct gnOutputDevice_t* device, struct gnPresentInfo_t info) {
    for (int i = 0; i < info.waitCount; i++) {
        while (!info.waitSemaphores[i].semaphore->eventTriggered) {}
    }

    info.presentationQueues->info.surface.windowSurface->layer.device = device->outputDevice->device;
    id<CAMetalDrawable> drawable = [info.presentationQueues->info.surface.windowSurface->layer nextDrawable];

    id<MTLCommandBuffer> commandBuffer = [device->outputDevice->queues[info.queueIndex] commandBuffer];

    MTLRenderPassDescriptor* passDesc = [MTLRenderPassDescriptor renderPassDescriptor];
    passDesc.colorAttachments[0].texture = drawable.texture;
    passDesc.colorAttachments[0].loadAction = MTLLoadActionClear;
    passDesc.colorAttachments[0].storeAction = MTLStoreActionStore;
    passDesc.colorAttachments[0].clearColor = MTLClearColorMake(1.0f, 0, 0, 1.0f);
    id<MTLRenderCommandEncoder> render = [commandBuffer renderCommandEncoderWithDescriptor:passDesc];
    [render endEncoding];

    [commandBuffer presentDrawable:drawable];
    [commandBuffer commit];


    return GN_SUCCESS;
}
