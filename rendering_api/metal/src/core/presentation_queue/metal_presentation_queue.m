#include "metal_presentation_queue.h"
#include "core/surface/metal_surface.h"
#include "core/devices/metal_output_devices.h"

gnReturnCode gnCreatePresentationQueueFn(gnPresentationQueue* presentationQueue, const gnOutputDevice* device, struct gnPresentationQueueInfo_t presentationInfo) {
    presentationQueue->presentationQueue = malloc(sizeof(struct gnPlatformPresentationQueue_t));

    MTLPixelFormat convertedFormat = mtlGryphnFormatToVulkanFormat(presentationInfo.format.format);
    CGColorSpaceRef convertedColorSpace = mtlGryphnColorSpaceToVulkanColorSpace(presentationInfo.format.colorSpace);

    presentationQueue->presentationQueue->textureCount = presentationInfo.ImageCount;
    presentationQueue->presentationQueue->textures = malloc(sizeof(id<MTLTexture>) * presentationInfo.ImageCount);

    MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.pixelFormat = convertedFormat;
    textureDescriptor.width = presentationInfo.ImageSize.x;
    textureDescriptor.height = presentationInfo.ImageSize.y;
    textureDescriptor.usage = MTLTextureUsageRenderTarget;
    textureDescriptor.textureType  = MTLTextureType2D;


    for (int i = 0; i < presentationInfo.ImageCount; i++) {
        presentationQueue->presentationQueue->textures[i] = [device->outputDevice->device newTextureWithDescriptor:textureDescriptor];
    }

    return GN_SUCCESS;
}
