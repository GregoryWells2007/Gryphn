#include "metal_present.h"
#include <synchronization/commands/gryphn_sync_present.h>

#include "time.h"

gnReturnCode metalPresent(gnOutputDeviceHandle device, gnPresentInfo info) {
    for (uint32_t i =0 ; i < info.presentationQueueCount; i++) {
    info.presentationQueues[i]->info.surface->windowSurface->layer.device = device->outputDevice->device;
    id<CAMetalDrawable> drawable = [info.presentationQueues[i]->info.surface->windowSurface->layer nextDrawable];
    if (drawable == nil) return GN_UNKNOWN_ERROR;

    __block gnPresentationQueue presentationQueue = info.presentationQueues[i];
    __block uint32_t imageIndex = info.imageIndices[i];

    id<MTLCommandBuffer> commandBuffer = [device->outputDevice->transferQueue commandBuffer];
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
        if (buffer == nil) return;
        uint32_tArrayListAdd(presentationQueue->presentationQueue->avaliableTextures, imageIndex);
    }];

        id<MTLBlitCommandEncoder> blit = [commandBuffer blitCommandEncoder];
        [blit copyFromTexture:info.presentationQueues[i]->images[info.imageIndices[i]]->texture->texture
                sourceSlice:0
                sourceLevel:0
                sourceOrigin:(MTLOrigin){0, 0, 0}
                sourceSize:(MTLSize){info.presentationQueues[i]->info.imageSize.x, info.presentationQueues[i]->info.imageSize.y, 1}
                toTexture:drawable.texture
            destinationSlice:0
            destinationLevel:0
        destinationOrigin:(MTLOrigin){0, 0, 0}];

        [blit endEncoding];

        [drawable texture];

        [commandBuffer presentDrawable:drawable];
        [commandBuffer commit];
        device->outputDevice->executingCommandBuffer = commandBuffer;
    }

    [device->outputDevice->executingCommandBuffer waitUntilCompleted];

    for (uint32_t i = 0; i < info.presentationQueueCount; i++) {
        if (info.presentationQueues[i]->info.imageSize.x != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.width ||
            info.presentationQueues[i]->info.imageSize.y != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.height) {
                return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
            }
    }

    return GN_SUCCESS;
}

gnReturnCode metalPresentSync(gnOutputDeviceHandle device, gnPresentSyncInfo info) {
    for (uint32_t i = 0; i < info.presentationQueueCount; i++) {
        if (info.presentationQueues[i]->info.surface->windowSurface->layer.device == nil) info.presentationQueues[i]->info.surface->windowSurface->layer.device = device->outputDevice->device;
        info.presentationQueues[i]->info.surface->windowSurface->layer.pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
        id<CAMetalDrawable> drawable = [info.presentationQueues[i]->info.surface->windowSurface->layer nextDrawable];
        if (drawable == nil) return GN_UNKNOWN_ERROR;

        __block gnPresentationQueue presentationQueue = info.presentationQueues[i];
        __block uint32_t imageIndex = info.imageIndices[i];

        id<MTLCommandBuffer> commandBuffer = [device->outputDevice->transferQueue commandBuffer];

        for (uint32_t c = 0; c < info.waitCount; c++) mtlWaitSemaphore(info.waitSemaphores[c], commandBuffer);

        [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
            if (buffer == nil) return;
            mtlAddImageBackToQueue(presentationQueue, imageIndex);
        }];

        MTLRenderPassDescriptor *desc = [MTLRenderPassDescriptor renderPassDescriptor];
        desc.colorAttachments[0].texture = drawable.texture;
        desc.colorAttachments[0].loadAction = MTLLoadActionClear;
        desc.colorAttachments[0].storeAction = MTLStoreActionStore;
        desc.colorAttachments[0].clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);

        id<MTLRenderCommandEncoder> enc = [commandBuffer renderCommandEncoderWithDescriptor:desc];

        [enc setRenderPipelineState:device->outputDevice->fullScreenPipeline];
        [enc setVertexBuffer:device->outputDevice->fullScreenQuadBuffer offset:0 atIndex:0];
        [enc setFragmentTexture:info.presentationQueues[i]->images[info.imageIndices[i]]->texture->texture atIndex:0];
        [enc drawPrimitives:MTLPrimitiveTypeTriangleStrip vertexStart:0 vertexCount:4];
        [enc endEncoding];

        [commandBuffer presentDrawable:drawable];
        [commandBuffer commit];
        device->outputDevice->executingCommandBuffer = commandBuffer;
    }

    for (uint32_t  i = 0; i < info.presentationQueueCount; i++) {
        if (info.presentationQueues[i]->info.imageSize.x != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.width ||
            info.presentationQueues[i]->info.imageSize.y != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.height) {
                return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
        }
    }

    return GN_SUCCESS;
}
