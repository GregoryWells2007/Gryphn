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

    MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.pixelFormat = convertedFormat;
    textureDescriptor.width = presentationInfo.imageSize.x;
    textureDescriptor.height = presentationInfo.imageSize.y;
    textureDescriptor.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
    textureDescriptor.textureType  = MTLTextureType2D;

    presentationQueue->imageCount = presentationInfo.minImageCount;
    presentationQueue->images = malloc(sizeof(gnTexture) * presentationInfo.minImageCount);
    presentationQueue->presentationQueue->textures = metalTextureArrayListCreate();
    presentationQueue->presentationQueue->avaliableTextures = uint32_tArrayListCreate();
    for (int i = 0; i < presentationInfo.minImageCount; i++) {
        presentationQueue->images[i] = malloc(sizeof(struct gnTexture_t));
        presentationQueue->images[i]->texture = malloc(sizeof(gnPlatformTexture));
        presentationQueue->images[i]->texture->texture = [device->outputDevice->device newTextureWithDescriptor:textureDescriptor];
        metalTextureArrayListAdd(&presentationQueue->presentationQueue->textures, presentationQueue->images[i]->texture->texture);
        uint32_tArrayListAdd(&presentationQueue->presentationQueue->avaliableTextures, i);
    }
    [textureDescriptor release];

    return GN_SUCCESS;
}

gnReturnCode getMetalPresentQueueImage(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphore semaphore, uint32_t* imageIndex) {
    while (presentationQueue->presentationQueue->avaliableTextures.count == 0) {}
    *imageIndex = presentationQueue->presentationQueue->avaliableTextures.data[0];
    uint32_tArrayListPopHead(&presentationQueue->presentationQueue->avaliableTextures);
    semaphore->semaphore->eventTriggered = gnTrue;
    return GN_SUCCESS;
}

void destroyMetalPresentationQueue(gnPresentationQueueHandle presentationQueue) {
    free(presentationQueue->presentationQueue->avaliableTextures.data);
    presentationQueue->presentationQueue->avaliableTextures.count = 0;
    for (int i = 0; i < presentationQueue->imageCount; i++) {
        [presentationQueue->images[i]->texture->texture release];
        free(presentationQueue->images[i]->texture);
        free(presentationQueue->images[i]);
    }
    free(presentationQueue->presentationQueue);
}
