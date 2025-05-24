#pragma once
#include <core/instance/gryphn_instance.h>
#include <platform/gryphn_platform_include.h>
#include <utils/types/gryphn_image_format.h>
#include "core/output_device/gryphn_physical_output_device.h"

struct gnPlatformWindowSurface_t;

typedef struct gnSurfaceFormat_t {
    gnImageFormat format;
    gnColorSpace colorSpace;
} gnSurfaceFormat;

typedef struct gnSurfaceDetails_t {
    uint32_t formatCount;
    struct gnSurfaceFormat_t* formats;

    uint32_t minImageCount, maxImageCount;
} gnSufaceDetails;

typedef struct gnWindowSurface_t {
    struct gnPlatformWindowSurface_t* windowSurface;
    gnInstance* instance;
} gnWindowSurface;
void gnDestroyWindowSurface(struct gnWindowSurface_t* windowSurface);
struct gnSurfaceFormat_t* gnGetSupportedSurfaceFormats(
    struct gnWindowSurface_t windowSurface,
    struct gnPhysicalDevice_t device,
    uint32_t* formatCount
);
gnBool gnIsSurfaceFormatSupported(
    struct gnWindowSurface_t windowSurface,
    struct gnPhysicalDevice_t device,
    struct gnSurfaceFormat_t format
);
// this function will give you you're preferred surface format
// unless its not supported then it will give you the first supported surface format
// at some point this function will attempt to give you the most simmilar surface format
struct gnSurfaceFormat_t gnGetPreferredSurfaceFormat(
    struct gnWindowSurface_t windowSurface,
    struct gnPhysicalDevice_t device,
    struct gnSurfaceFormat_t format
);
uint32_t gnGetMinImageCount(struct gnWindowSurface_t surface, struct gnPhysicalDevice_t device);
uint32_t gnGetMaxImageCount(struct gnWindowSurface_t surface, struct gnPhysicalDevice_t device);
uint32_t gnGetPreferredImageCount(struct gnWindowSurface_t surface, struct gnPhysicalDevice_t device);
