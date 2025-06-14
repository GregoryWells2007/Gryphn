#include "gryphn_surface.h"
#include "core/gryphn_platform_functions.h"

void gnDestroyWindowSurface(gnWindowSurfaceHandle windowSurface) {
    windowSurface->instance->functions->_gnDestroyWindowSurface(windowSurface);
}

struct gnSurfaceFormat_t* gnGetSupportedSurfaceFormats(
    gnWindowSurfaceHandle windowSurface,
    struct gnPhysicalDevice_t device,
    uint32_t* formatCount
) {
    gnSurfaceDetails surfaceDetails = windowSurface->instance->functions->_gnGetSurfaceDetails(windowSurface, device);
    *formatCount = surfaceDetails.formatCount;
    return surfaceDetails.formats;
}

gnBool gnIsSurfaceFormatSupported(
    gnWindowSurfaceHandle windowSurface,
    struct gnPhysicalDevice_t device,
    struct gnSurfaceFormat_t format
) {
    uint32_t formatCount = 0;
    gnSurfaceFormat* formats = gnGetSupportedSurfaceFormats(windowSurface, device, &formatCount);
    for (int i = 0; i < formatCount; i++) {
        if (formats[i].format == format.format && formats[i].colorSpace == format.colorSpace) {
            return gnTrue;
        }
    }
    return gnFalse;
}

struct gnSurfaceFormat_t gnGetPreferredSurfaceFormat(
    gnWindowSurfaceHandle windowSurface,
    struct gnPhysicalDevice_t device,
    struct gnSurfaceFormat_t format
) {
    uint32_t formatCount = 0;
    gnSurfaceFormat* formats = gnGetSupportedSurfaceFormats(windowSurface, device, &formatCount);
    for (int i = 0; i < formatCount; i++) {
        if (formats[i].format == format.format && formats[i].colorSpace == format.colorSpace) {
            return formats[i];
        }
    }

    // will attempt to give you a simmilar format that either matches the Image format and the Color space
    for (int i = 0; i < formatCount; i++) {
        if (formats[i].format == format.format || formats[i].colorSpace == format.colorSpace) {
            return formats[i];
        }
    }

    return formats[0];
}

uint32_t gnGetMinImageCount(gnWindowSurfaceHandle  surface, struct gnPhysicalDevice_t device) {
    gnSurfaceDetails surfaceDetails = surface->instance->functions->_gnGetSurfaceDetails(surface, device);
    return surfaceDetails.minImageCount;
}
uint32_t gnGetMaxImageCount(gnWindowSurfaceHandle  surface, struct gnPhysicalDevice_t device) {
    gnSurfaceDetails surfaceDetails = surface->instance->functions->_gnGetSurfaceDetails(surface, device);
    return surfaceDetails.maxImageCount;
}

uint32_t gnGetPreferredImageCount(gnWindowSurfaceHandle  surface, struct gnPhysicalDevice_t device) {
    gnSurfaceDetails surfaceDetails = surface->instance->functions->_gnGetSurfaceDetails(surface, device);

    uint32_t imageCount = surfaceDetails.minImageCount + 1;
    if (surfaceDetails.maxImageCount > 0 && imageCount > surfaceDetails.maxImageCount) {
        imageCount = surfaceDetails.maxImageCount;
    }
    return imageCount;
}

gnSurfaceDetails gnGetSurfaceDetails(gnWindowSurfaceHandle surface, gnPhysicalDevice device) { return surface->instance->functions->_gnGetSurfaceDetails(surface, device); }
