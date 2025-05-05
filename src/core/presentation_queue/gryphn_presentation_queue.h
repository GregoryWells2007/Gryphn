#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_presentation_details.h"
#include "core/output_device/gryphn_output_device.h"
#include "core/sync_objects/gryphn_sync_semaphore.h"
#include "gryphn_present_queue_state.h"
#include "core/textures/gryphn_texture.h"
#include "gryphn_device_presentation_details.h"

struct gnPlatformPresentationQueue;

struct gnPresentationQueue {
ACCESS_LEVEL:
    gnPlatformPresentationQueue* presentationQueue;
    bool valid = false;
    gnList<gnTexture> images = gnCreateList<gnTexture>();
public:
    gnPresentationQueue() {}
};

gnTexture* gnGetPresentationQueueImage(gnPresentationQueue& presentationQueue, int index);

inline gnReturnCode (*gnCreatePresentationQueue)(gnPresentationQueue* presentationQueue, const gnOutputDevice& device, gnPresentationDetails& details);
inline void (*gnDestroyPresentationQueue)(gnPresentationQueue& queue);
inline gnImageFormat (*_gnPresentationQueueGetImageFormat)(gnPresentationQueue& presentationQueue);
inline gnImageFormat gnPresentationQueueGetImageFormat(gnPresentationQueue& presentationQueue) {
    std::cout << "gnPresentationQueueGetImageFormat should lowkey become supported\n";
    return _gnPresentationQueueGetImageFormat(presentationQueue);
}
inline gnPresentationQueueState (*gnPresentationQueueGetState)(gnPresentationQueue& presentationQueue);
inline gnReturnCode (*gnPresentationQueueGetNextImageAsync)(gnPresentationQueue& presentationQueue, const gnSyncSemaphore& semaphore, gnUInt* imageIndex);
