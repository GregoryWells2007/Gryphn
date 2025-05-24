#include "gryphn_surface.h"
#include "core/gryphn_platform_functions.h"

void gnDestroyWindowSurface(struct gnWindowSurface_t *windowSurface) {
    windowSurface->instance->functions->_gnDestroyWindowSurface(windowSurface);
}

struct gnSurfaceFormat_t* gnGetSupportedSurfaceFormats(
    struct gnWindowSurface_t* windowSurface,
    struct gnPhysicalDevice_t device,
    uint32_t* formatCount
) {
    struct gnSurfaceDetails_t surfaceDetails = windowSurface->instance->functions->_gnGetSurfaceDetails(windowSurface, device);
    *formatCount = surfaceDetails.formatCount;
    return surfaceDetails.formats;
}

gnBool gnIsSurfaceFormatSupported(
    struct gnWindowSurface_t* windowSurface,
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
    struct gnWindowSurface_t* windowSurface,
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

int gnGetMinImageCount(struct gnWindowSurface_t surface, struct gnPhysicalDevice_t device) {
    struct gnSurfaceDetails_t surfaceDetails = surface.instance->functions->_gnGetSurfaceDetails(&surface, device);
    return surfaceDetails.minImageCount;
}
int gnGetMaxImageCount(struct gnWindowSurface_t surface, struct gnPhysicalDevice_t device) {
    struct gnSurfaceDetails_t surfaceDetails = surface.instance->functions->_gnGetSurfaceDetails(&surface, device);
    return surfaceDetails.maxImageCount;
}
