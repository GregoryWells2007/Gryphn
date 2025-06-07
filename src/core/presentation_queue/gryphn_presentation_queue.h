#pragma once
#include <gryphn/gryphn_utils.h>
#include <core/output_device/gryphn_output_device.h>
#include <core/window_surface/gryphn_surface.h>
#include <utils/gryphn_image_format.h>
#include <core/sync/semaphore/gryphn_semaphore.h>
#include "core/gryphn_handles.h"

typedef struct gnPresentationQueueInfo_t {
    uint32_t minImageCount;
    gnUInt2 imageSize;
    gnWindowSurfaceHandle surface;
    gnSurfaceFormat format;
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
    struct gnPresentationQueueInfo_t info;
};
#endif

gnReturnCode gnCreatePresentationQueue(gnPresentationQueueHandle* presentationQueue, gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo);
gnReturnCode gnPresentationQueueGetImage(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex);
uint32_t gnGetPresentationQueueImageCount(gnPresentationQueueHandle presentationQueue);
gnTextureHandle gnGetPresentationQueueImage(gnPresentationQueueHandle presentationQueue, uint32_t index);
void gnDestroyPresentationQueue(gnPresentationQueueHandle presentationQueue);
