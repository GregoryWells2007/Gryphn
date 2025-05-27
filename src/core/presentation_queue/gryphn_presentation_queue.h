#pragma once
#include <gryphn/gryphn_utils.h>
#include <core/output_device/gryphn_output_device.h>
#include <core/window_surface/gryphn_surface.h>
#include <utils/types/gryphn_image_format.h>

typedef struct gnPresentationQueueInfo_t {
    uint32_t minImageCount;
    struct gnUInt2_t imageSize;
    struct gnWindowSurface_t surface;
    struct gnSurfaceFormat_t format;
    enum gnImageSharingMode_e imageSharingMode;
    uint32_t queueFamilyCount;
    uint32_t* queueFamilies;
} gnPresentationQueueInfo;

struct gnPlatformPresentationQueue_t;

typedef struct gnPresentationQueue_t {
    struct gnPlatformPresentationQueue_t* presentationQueue;
    struct gnOutputDevice_t* outputDevice;
    gnBool valid;
    int imageCount;
} gnPresentationQueue;

gnReturnCode gnCreatePresentationQueue(gnPresentationQueue* presentationQueue, struct gnOutputDevice_t* device, struct gnPresentationQueueInfo_t presentationInfo);
void gnDestroyPresentationQueue(gnPresentationQueue* presentationQueue);
