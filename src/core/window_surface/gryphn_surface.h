#pragma once
#include <core/instance/gryphn_instance.h>
#include <platform/gryphn_platform_include.h>
#include <utils/types/gryphn_image_format.h>
#include "core/output_device/gryphn_physical_output_device.h"

typedef struct gnSurfaceFormat_t {
    gnImageFormat format;
    gnColorSpace colorSpace;
} gnSurfaceFormat;

typedef struct gnSurfaceDetails_t {
    uint32_t formatCount;
    struct gnSurfaceFormat_t* formats;

    uint32_t minImageCount, maxImageCount;
} gnSufaceDetails;

#ifdef GN_REVEAL_IMPL
struct gnWindowSurface_t {
    struct gnPlatformWindowSurface_t* windowSurface;
    gnInstanceHandle instance;
};
#endif
// typedef struct gnWindowSurface_t* gnWindowSurfaceHandle;


void gnDestroyWindowSurface(gnWindowSurfaceHandle windowSurface);
struct gnSurfaceFormat_t* gnGetSupportedSurfaceFormats(
    gnWindowSurfaceHandle windowSurface,
    struct gnPhysicalDevice_t device,
    uint32_t* formatCount
);
gnBool gnIsSurfaceFormatSupported(
    gnWindowSurfaceHandle windowSurface,
    struct gnPhysicalDevice_t device,
    struct gnSurfaceFormat_t format
);
// this function will give you you're preferred surface format
// unless its not supported then it will give you the first supported surface format
// at some point this function will attempt to give you the most simmilar surface format
struct gnSurfaceFormat_t gnGetPreferredSurfaceFormat(
    gnWindowSurfaceHandle windowSurface,
    struct gnPhysicalDevice_t device,
    struct gnSurfaceFormat_t format
);
uint32_t gnGetMinImageCount(gnWindowSurfaceHandle surface, struct gnPhysicalDevice_t device);
uint32_t gnGetMaxImageCount(gnWindowSurfaceHandle surface, struct gnPhysicalDevice_t device);
uint32_t gnGetPreferredImageCount(gnWindowSurfaceHandle surface, struct gnPhysicalDevice_t device);
