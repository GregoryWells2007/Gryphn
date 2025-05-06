#define GN_TEXTURE_NO_TEXTURE_ID
#include <core/presentation_queue/gryphn_device_presentation_details.h>
#include <core/presentation_queue/gryphn_presentation_queue.h>
#include "core/devices/metal_output_devices.h"
#include "core/metal_instance.h"
#include "core/textures/metal_texture.h"
#include "QuartzCore/CAMetalLayer.h"
#include "core/sync_objects/metal_semaphore.h"
#include "bridge/metal_bridge.h"
#include "metal_presentation_queue.h"

gnOutputDevice* mltGetOutputDevice(gnPlatformPresentationQueue* presentaionQueue) {
    return presentaionQueue->outputDevice;
}

#define MAXIMUM_DRAWABLES 3

GN_EXPORT gnDevicePresentationDetails gnGetDevicePresentationDetailsFn(const gnPhysicalOutputDevice& physicalOutputDevice) {
    return { MAXIMUM_DRAWABLES, MAXIMUM_DRAWABLES };
}

GN_EXPORT gnReturnCode gnPresentationQueueGetNextImageAsyncFn(gnPresentationQueue& presentationQueue, const gnSyncSemaphore& semaphore, gnUInt* imageIndex) {
    mtlObjectCSetContentViewsLayer(
        presentationQueue.presentationQueue->outputDevice->outputDevice->instance->instance->window,
        presentationQueue.presentationQueue->layer);

    presentationQueue.presentationQueue->currentDrawableIndex++;
    presentationQueue.presentationQueue->currentDrawableIndex %= MAXIMUM_DRAWABLES;
    *imageIndex = presentationQueue.presentationQueue->currentDrawableIndex;

    presentationQueue.presentationQueue->currentDrawable = presentationQueue.presentationQueue->layer->nextDrawable();

    dispatch_semaphore_signal(semaphore.semaphore->semaphore);
    return GN_SUCCESS;
}

GN_EXPORT gnPresentationQueueState gnPresentationQueueGetStateFn(gnPresentationQueue& presentationQueue) {
    return GN_VALID;
}

GN_EXPORT gnReturnCode gnCreatePresentationQueueFn(gnPresentationQueue* presentationQueue, const gnOutputDevice& device, gnPresentationDetails& details) {
    presentationQueue->presentationQueue = new gnPlatformPresentationQueue();
    presentationQueue->presentationQueue->outputDevice = const_cast<gnOutputDevice*>(&device);

    presentationQueue->presentationQueue->layer = CA::MetalLayer::layer();
    presentationQueue->presentationQueue->layer->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    presentationQueue->presentationQueue->layer->setFramebufferOnly(true);
    presentationQueue->presentationQueue->layer->setDrawableSize({ (double)details.ImageSize.x, (double)details.ImageSize.y });
    presentationQueue->presentationQueue->layer->setDevice(device.outputDevice->device);

    mtlInitializeMetalLayer(presentationQueue->presentationQueue->layer, true);

    mtlObjectCSetContentViewsLayer(
        device.outputDevice->instance->instance->window,
        presentationQueue->presentationQueue->layer);

    for (int i = 0; i < details.ImageCount; i++) {
        MTL::TextureDescriptor* desc = MTL::TextureDescriptor::texture2DDescriptor(
            MTL::PixelFormat::PixelFormatBGRA8Unorm,
            details.ImageSize.x,
            details.ImageSize.y,
            false
        );
        desc->setUsage(MTL::TextureUsageRenderTarget | MTL::TextureUsageShaderRead);

        gnTexture newImage = gnTexture();
        newImage.textureColorFormat = GN_BGRA8;
        newImage.minFilter = GN_FILTER_NEAREST;
        newImage.magFilter = GN_FILTER_NEAREST;
        newImage.textureType = GN_TEXTURE_2D;
        newImage.texture = new gnPlatformTexture();
        newImage.texture->texture = device.outputDevice->device->newTexture(desc);
        gnListAdd(presentationQueue->images, newImage);
    }

    MTL::TextureDescriptor* afsdfsdf = MTL::TextureDescriptor::texture2DDescriptor(
        MTL::PixelFormat::PixelFormatBGRA8Unorm,
        2,
        2,
        false
    );
    afsdfsdf->setUsage(MTL::TextureUsageRenderTarget | MTL::TextureUsageShaderRead);

    gnTexture newImage = gnTexture();
    newImage.textureColorFormat = GN_BGRA8;
    newImage.minFilter = GN_FILTER_NEAREST;
    newImage.magFilter = GN_FILTER_NEAREST;
    newImage.textureType = GN_TEXTURE_2D;
    newImage.texture = new gnPlatformTexture();
    newImage.texture->texture = device.outputDevice->device->newTexture(afsdfsdf);
    MTL::Region region = MTL::Region(0, 0, 2, 2);
    uint32_t data[4] = {
        0xffffffff, 0xff000000, 0xffff0000, 0xffffff00
    };
    newImage.texture->texture->replaceRegion(region, 0, data, 8);

    gnListAdd(presentationQueue->images, newImage);

    // so funny story I have no god damn clue how to implement a presentation queue on metal
    return GN_SUCCESS;
}
GN_EXPORT void gnDestroyPresentationQueueFn(gnPresentationQueue& queue) {
    for (int i = 0; i < gnListLength(queue.images); i++) {
        gnDestroyTexture(queue.images[i]);
    }
    queue.images = gnCreateList<gnTexture>();
}
