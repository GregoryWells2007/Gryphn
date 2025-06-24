#include "gryphn_surface.h"

void gnDestroyWindowSurface(gnWindowSurfaceHandle windowSurface) {
    windowSurface->instance->instanceFunctions._gnDestroyWindowSurface(windowSurface);
}

gnSurfaceFormat* gnGetSupportedSurfaceFormats(
    gnWindowSurfaceHandle windowSurface,
    gnPhysicalDevice device,
    uint32_t* formatCount
) {
    gnSurfaceDetails surfaceDetails = windowSurface->instance->instanceFunctions._gnGetSurfaceDetails(windowSurface, device);
    *formatCount = surfaceDetails.formatCount;
    return surfaceDetails.formats;
}

gnBool gnIsSurfaceFormatSupported(
    gnWindowSurfaceHandle windowSurface,
    gnPhysicalDevice device,
    gnSurfaceFormat format
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

gnSurfaceFormat gnGetPreferredSurfaceFormat(
    gnWindowSurfaceHandle windowSurface,
    gnPhysicalDevice device,
    gnSurfaceFormat format
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

uint32_t gnGetMinImageCount(gnWindowSurfaceHandle  surface, gnPhysicalDevice device) {
    gnSurfaceDetails surfaceDetails = surface->instance->instanceFunctions._gnGetSurfaceDetails(surface, device);
    return surfaceDetails.minImageCount;
}
uint32_t gnGetMaxImageCount(gnWindowSurfaceHandle  surface, gnPhysicalDevice device) {
    gnSurfaceDetails surfaceDetails = surface->instance->instanceFunctions._gnGetSurfaceDetails(surface, device);
    return surfaceDetails.maxImageCount;
}

uint32_t gnGetPreferredImageCount(gnWindowSurfaceHandle  surface, gnPhysicalDevice device) {
    gnSurfaceDetails surfaceDetails = surface->instance->instanceFunctions._gnGetSurfaceDetails(surface, device);

    uint32_t imageCount = surfaceDetails.minImageCount + 1;
    if (surfaceDetails.maxImageCount > 0 && imageCount > surfaceDetails.maxImageCount) {
        imageCount = surfaceDetails.maxImageCount;
    }
    return imageCount;
}

gnSurfaceDetails gnGetSurfaceDetails(gnWindowSurfaceHandle surface, gnPhysicalDevice device) { return surface->instance->instanceFunctions._gnGetSurfaceDetails(surface, device); }
