#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/output_device/gryphn_output_device.h"
#include <core/window_surface/gryphn_surface.h>
// #include "core/sync_objects/gryphn_sync_semaphore.h"
// #include "core/textures/gryphn_texture.h"
// #include "gryphn_device_presentation_details.h"

typedef struct gnPresentationQueueInfo_t {
    gnUInt ImageCount;
    gnUInt2 ImageSize;
    struct gnWindowSurface_t surface;
} gnPresentationQueueInfo;

struct gnPlatformPresentationQueue_t;

typedef struct gnPresentationQueue_t {
    struct gnPlatformPresentationQueue* presentationQueue;
    gnBool valid;
    // uint32_t textureCount;
    // gnTexture* texturs;
} gnPresentationQueue;

// gnTexture* gnGetPresentationQueueImage(gnPresentationQueue& presentationQueue, int index);

gnReturnCode gnCreatePresentationQueue(gnPresentationQueue* presentationQueue, const gnOutputDevice* device, struct gnPresentationQueueInfo_t presentationInfo);

// inline gnReturnCode (*gnCreatePresentationQueue)(gnPresentationQueue* presentationQueue, const gnOutputDevice& device, gnPresentationDetails& details);
// inline void (*gnDestroyPresentationQueue)(gnPresentationQueue& queue);
// inline gnImageFormat (*_gnPresentationQueueGetImageFormat)(gnPresentationQueue& presentationQueue);
// inline gnImageFormat gnPresentationQueueGetImageFormat(gnPresentationQueue& presentationQueue) {
    // std::cout << "gnPresentationQueueGetImageFormat should lowkey become supported\n";
    // return _gnPresentationQueueGetImageFormat(presentationQueue);
// }
// inline gnPresentationQueueState (*gnPresentationQueueGetState)(gnPresentationQueue& presentationQueue);
// inline gnReturnCode (*gnPresentationQueueGetNextImageAsync)(gnPresentationQueue& presentationQueue, const gnSyncSemaphore& semaphore, gnUInt* imageIndex);
