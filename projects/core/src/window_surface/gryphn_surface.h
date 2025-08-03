#pragma once
#include <gryphn_platform_include.h>
#include <core/gryphn_image_format.h>
#include <instance/gryphn_instance.h>
#include "utils/math/gryphn_vec2.h"

typedef struct gnSurfaceFormat {
    gnImageFormat format;
    gnColorSpace colorSpace;
} gnSurfaceFormat;

typedef struct gnSurfaceDetails {
    uint32_t formatCount;
    gnSurfaceFormat* formats;

    uint32_t minImageCount, maxImageCount;
    gnUInt2 minImageSize, maxImageSize, currentSize;
} gnSurfaceDetails;

#ifdef GN_REVEAL_IMPL
struct gnWindowSurface_t {
    struct gnPlatformWindowSurface_t* windowSurface;
    gnInstanceHandle instance;
};
#endif
// typedef struct gnWindowSurface_t* gnWindowSurfaceHandle;


void gnDestroyWindowSurface(gnWindowSurfaceHandle windowSurface);
gnSurfaceFormat* gnGetSupportedSurfaceFormats(
    gnWindowSurfaceHandle windowSurface,
    gnPhysicalDevice device,
    uint32_t* formatCount
);
gnBool gnIsSurfaceFormatSupported(
    gnWindowSurfaceHandle windowSurface,
    gnPhysicalDevice device,
    gnSurfaceFormat format
);
// this function will give you you're preferred surface format
// unless its not supported then it will give you the first supported surface format
// at some point this function will attempt to give you the most simmilar surface format
gnSurfaceFormat gnGetPreferredSurfaceFormat(
    gnWindowSurfaceHandle windowSurface,
    gnPhysicalDevice device,
    gnSurfaceFormat format
);
uint32_t gnGetMinImageCount(gnWindowSurfaceHandle surface, gnPhysicalDevice device);
uint32_t gnGetMaxImageCount(gnWindowSurfaceHandle surface, gnPhysicalDevice device);
uint32_t gnGetPreferredImageCount(gnWindowSurfaceHandle surface, gnPhysicalDevice device);


gnSurfaceDetails gnGetSurfaceDetails(gnWindowSurfaceHandle surface, gnPhysicalDevice device);
