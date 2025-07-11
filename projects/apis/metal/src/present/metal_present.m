#include "metal_present.h"
#include <synchronization/commands/gryphn_sync_present.h>

#include "stdio.h"
#include "time.h"

gnReturnCode metalPresent(gnOutputDeviceHandle device, gnPresentInfo info) {
    for (int i =0 ; i < info.presentationQueueCount; i++) {
    info.presentationQueues[i]->info.surface->windowSurface->layer.device = device->outputDevice->device;
    id<CAMetalDrawable> drawable = [info.presentationQueues[i]->info.surface->windowSurface->layer nextDrawable];
    if (drawable == nil) return GN_FAILED_TO_CREATE_FRAMEBUFFER;

    __block gnPresentationQueue presentationQueue = info.presentationQueues[i];
    __block uint32_t imageIndex = info.imageIndices[i];

    id<MTLCommandBuffer> commandBuffer = [device->outputDevice->transferQueue commandBuffer];
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
        uint32_tArrayListAdd(&presentationQueue->presentationQueue->avaliableTextures, imageIndex);
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

        [commandBuffer presentDrawable:drawable];
        [commandBuffer commit];
        device->outputDevice->executingCommandBuffer = commandBuffer;
    }

    [device->outputDevice->executingCommandBuffer waitUntilCompleted];

    for (int  i = 0; i < info.presentationQueueCount; i++) {
        if (info.presentationQueues[i]->info.imageSize.x != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.width ||
            info.presentationQueues[i]->info.imageSize.y != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.height) {
                return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
            }
    }

    return GN_SUCCESS;
}

gnReturnCode metalPresentSync(gnOutputDeviceHandle device, gnPresentSyncInfo info) {
    clock_t begin = clock();
    for (int i = 0; i < info.waitCount; i++) {
        while (!info.waitSemaphores[i]->semaphore->eventTriggered) {}
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent waiting to present: %lf\n", time_spent);

    for (int i =0 ; i < info.presentationQueueCount; i++) {
    info.presentationQueues[i]->info.surface->windowSurface->layer.device = device->outputDevice->device;
    id<CAMetalDrawable> drawable = [info.presentationQueues[i]->info.surface->windowSurface->layer nextDrawable];
    if (drawable == nil) return GN_FAILED_TO_CREATE_FRAMEBUFFER;

    __block gnPresentationQueue presentationQueue = info.presentationQueues[i];
    __block uint32_t imageIndex = info.imageIndices[i];

    id<MTLCommandBuffer> commandBuffer = [device->outputDevice->transferQueue commandBuffer];
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
        mtlAddImageBackToQueue(presentationQueue, imageIndex);
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

        [commandBuffer presentDrawable:drawable];
        [commandBuffer commit];
        device->outputDevice->executingCommandBuffer = commandBuffer;
    }

    // [device->outputDevice->executingCommandBuffer waitUntilScheduled];

    for (int  i = 0; i < info.presentationQueueCount; i++) {
        if (info.presentationQueues[i]->info.imageSize.x != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.width ||
            info.presentationQueues[i]->info.imageSize.y != info.presentationQueues[i]->info.surface->windowSurface->layer.drawableSize.height) {
                return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
            }
    }

    return GN_SUCCESS;
}
