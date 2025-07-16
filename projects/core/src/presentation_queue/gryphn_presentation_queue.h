#pragma once
#include <utils/gryphn_image_format.h>
#include <output_device/gryphn_output_device.h>
#include <window_surface/gryphn_surface.h>
#include "gryphn_handles.h"

typedef struct gnPresentationQueueInfo {
    uint32_t minImageCount;
    gnUInt2 imageSize;
    gnWindowSurfaceHandle surface;
    gnSurfaceFormat format;

    // ignored unless GN_EXT_QUEUES is enabled
    gnImageSharingMode imageSharingMode;
    uint32_t queueFamilyCount;
    uint32_t* queueFamilies;
} gnPresentationQueueInfo;

struct gnPlatformPresentationQueue_t;

#ifdef GN_REVEAL_IMPL
struct gnPresentationQueue_t {
    struct gnPlatformPresentationQueue_t* presentationQueue;
    gnOutputDeviceHandle outputDevice;
    gnBool valid;
    uint32_t imageCount;
    gnTextureHandle* images;
    gnPresentationQueueInfo info;
};
#endif

gnReturnCode gnCreatePresentationQueue(gnPresentationQueueHandle* presentationQueue, gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo);
gnReturnCode gnPresentationQueueGetImage(gnPresentationQueue presentationQueue, uint32_t* imageIndex);
uint32_t gnGetPresentationQueueImageCount(gnPresentationQueueHandle presentationQueue);
gnTextureHandle gnGetPresentationQueueImage(gnPresentationQueueHandle presentationQueue, uint32_t index);
void gnDestroyPresentationQueue(gnPresentationQueueHandle presentationQueue);
