#include "metal_presentation_queue.h"
#include "surface/metal_surface.h"
#include "devices/metal_output_devices.h"
#include "texture/metal_texture.h"
#include "sync/semaphore/metal_semaphore.h"

gnReturnCode createMetalPresentationQueue(gnPresentationQueueHandle presentationQueue, const gnDevice device, gnPresentationQueueInfo presentationInfo) {
    presentationQueue->presentationQueue = malloc(sizeof(struct gnPlatformPresentationQueue_t));
    presentationQueue->presentationQueue->createdSize.x = presentationInfo.surface->windowSurface->layer.visibleRect.size.width;
    presentationQueue->presentationQueue->createdSize.y = presentationInfo.surface->windowSurface->layer.visibleRect.size.height;

    MTLPixelFormat convertedFormat = mtlGryphnFormatToMetalFormat(presentationInfo.format.format);

    MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.pixelFormat = convertedFormat;
    textureDescriptor.width = presentationInfo.imageSize.x;
    textureDescriptor.height = presentationInfo.imageSize.y;
    textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    textureDescriptor.sampleCount = 1;
    textureDescriptor.textureType  = MTLTextureType2D;

    presentationQueue->imageCount = presentationInfo.minImageCount;
    presentationQueue->images = malloc(sizeof(gnTexture) * presentationInfo.minImageCount);
    presentationQueue->presentationQueue->textures = metalTextureArrayListCreate();
    presentationQueue->presentationQueue->avaliableTextures = uint32_tArrayListCreate();
    for (uint32_t i = 0; i < presentationInfo.minImageCount; i++) {
        presentationQueue->images[i] = malloc(sizeof(struct gnTexture_t));
        presentationQueue->images[i]->texture = malloc(sizeof(gnPlatformTexture));
        presentationQueue->images[i]->texture->texture = [device->outputDevice->device newTextureWithDescriptor:textureDescriptor];
        metalTextureArrayListAdd(presentationQueue->presentationQueue->textures, presentationQueue->images[i]->texture->texture);
        uint32_tArrayListAdd(presentationQueue->presentationQueue->avaliableTextures, i);
    }
    [textureDescriptor release];

    return GN_SUCCESS;
}

void mtlTakeImageFromQueue(uint32_t* whereToPut, gnPresentationQueue queue, gnSemaphore semaphore) {
    *whereToPut = uint32_tArrayListAt(queue->presentationQueue->avaliableTextures, 0);
    uint32_tArrayListPopHead(queue->presentationQueue->avaliableTextures);
    if (!semaphore) return;
    id<MTLCommandBuffer> buffer = [queue->outputDevice->outputDevice->transferQueue commandBuffer];
    mtlSignalSemaphore(semaphore, buffer);
    [buffer commit];
}

void mtlAddImageBackToQueue(gnPresentationQueue queue, uint32_t index) {
    if (mtlImageNeededArrayListCount(queue->presentationQueue->neededImages) > 0) {
        mtlImageNeeded* needed = mtlImageNeededArrayListRefAt(queue->presentationQueue->neededImages, mtlImageNeededArrayListCount(queue->presentationQueue->neededImages) - 1);
        mtlTakeImageFromQueue(needed->whereToPut, queue, needed->semaphoreToSignal);
        mtlImageNeededArrayListRemove(queue->presentationQueue->neededImages);
    }
    else
        uint32_tArrayListAdd(queue->presentationQueue->avaliableTextures, index);
}

gnReturnCode getMetalPresentQueueImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphore semaphore, uint32_t* imageIndex) {
    time_t last_time = time(NULL);
    while(uint32_tArrayListCount(presentationQueue->presentationQueue->avaliableTextures) == 0 || timeout >= 0) {
        time_t curr_time = time(NULL);
        timeout -= (curr_time - last_time);
        last_time = curr_time;
    }
    mtlTakeImageFromQueue(imageIndex, presentationQueue, semaphore);

    CGSize currentSize = presentationQueue->info.surface->windowSurface->layer.visibleRect.size;
    if (currentSize.width  != presentationQueue->presentationQueue->createdSize.x ||
        currentSize.height != presentationQueue->presentationQueue->createdSize.y) return GN_SUBOPTIMAL_PRESENTATION_QUEUE;

    return GN_SUCCESS;
}

gnReturnCode getMetalPresentQueueImage(gnPresentationQueueHandle presentationQueue, uint32_t* imageIndex) {
    while(uint32_tArrayListCount(presentationQueue->presentationQueue->avaliableTextures) == 0);
    mtlTakeImageFromQueue(imageIndex, presentationQueue, NULL);

    CGSize currentSize = presentationQueue->info.surface->windowSurface->layer.visibleRect.size;
    if (currentSize.width  != presentationQueue->presentationQueue->createdSize.x ||
        currentSize.height != presentationQueue->presentationQueue->createdSize.y) return GN_SUBOPTIMAL_PRESENTATION_QUEUE;

    return GN_SUCCESS;
}

void destroyMetalPresentationQueue(gnPresentationQueueHandle presentationQueue) {
    for (uint32_t i = 0; i < presentationQueue->imageCount; i++) {
        [presentationQueue->images[i]->texture->texture release];
        free(presentationQueue->images[i]->texture);
        free(presentationQueue->images[i]);
    }
    free(presentationQueue->presentationQueue);
}


GN_ARRAY_LIST_DEFINITION(metalTexture)
GN_ARRAY_LIST_DEFINITION(mtlImageNeeded)
