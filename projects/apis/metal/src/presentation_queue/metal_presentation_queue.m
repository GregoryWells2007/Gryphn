#include "metal_presentation_queue.h"
#include "surface/metal_surface.h"
#include "devices/metal_output_devices.h"
#include "debugger/gryphn_debugger.h"
#include "texture/metal_texture.h"
#include "sync/semaphore/metal_semaphore.h"

gnReturnCode createMetalPresentationQueue(gnPresentationQueueHandle presentationQueue, const gnDevice device, gnPresentationQueueInfo presentationInfo) {
    if (presentationInfo.minImageCount > 3) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString("On Metal you cannot have more than 3 images in a presentation queue")
        });
        return GN_UNSUPPORTED_IMAGE_COUNT;
    }

    if (presentationInfo.minImageCount < 2) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString("On Metal you cannot have less than 2 images in a presentation queue")
        });
        return GN_UNSUPPORTED_IMAGE_COUNT;
    }

    presentationQueue->presentationQueue = malloc(sizeof(struct gnPlatformPresentationQueue_t));

    MTLPixelFormat convertedFormat = mtlGryphnFormatToMetalFormat(presentationInfo.format.format);
    CGColorSpaceRef convertedColorSpace = mtlGryphnColorSpaceToMetalColorSpace(presentationInfo.format.colorSpace);

    presentationQueue->presentationQueue->textureCount = presentationInfo.minImageCount;
    presentationQueue->presentationQueue->textures = malloc(sizeof(id<MTLTexture>) * presentationInfo.minImageCount);

    MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.pixelFormat = convertedFormat;
    textureDescriptor.width = presentationInfo.imageSize.x;
    textureDescriptor.height = presentationInfo.imageSize.y;
    textureDescriptor.usage = MTLTextureUsageRenderTarget;
    textureDescriptor.textureType  = MTLTextureType2D;

    presentationQueue->imageCount = presentationInfo.minImageCount;
    presentationQueue->images = malloc(sizeof(gnTexture) * presentationInfo.minImageCount);
    for (int i = 0; i < presentationInfo.minImageCount; i++) {
        presentationQueue->presentationQueue->textures[i] = [device->outputDevice->device newTextureWithDescriptor:textureDescriptor];
        presentationQueue->images[i] = malloc(sizeof(struct gnTexture_t));
        presentationQueue->images[i]->texture = malloc(sizeof(gnPlatformTexture));
        presentationQueue->images[i]->texture->texture = presentationQueue->presentationQueue->textures[i];
    }

    return GN_SUCCESS;
}

gnReturnCode getMetalPresentQueueImage(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphore semaphore, uint32_t* imageIndex) {
    semaphore->semaphore->eventTriggered = gnFalse;
    *imageIndex = presentationQueue->presentationQueue->currentImage;
    presentationQueue->presentationQueue->currentImage++;
    presentationQueue->presentationQueue->currentImage %= presentationQueue->imageCount;
    semaphore->semaphore->eventTriggered = gnTrue;
    return GN_SUCCESS;
}

void destroyMetalPresentationQueue(gnPresentationQueueHandle presentationQueue) {
    for (int i = 0; i < presentationQueue->imageCount; i++) {
        [presentationQueue->presentationQueue->textures[i] release];
    }
    free(presentationQueue->presentationQueue);
}
