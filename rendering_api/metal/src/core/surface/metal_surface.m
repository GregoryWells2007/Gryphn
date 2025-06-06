#include "metal_surface.h"
#include "core/window_surface/gryphn_surface_create_functions.h"

#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>
#import <CoreGraphics/CoreGraphics.h>

gnReturnCode gnCreateMacOSWindowSurfaceFn(struct gnWindowSurface_t* windowSurface, gnInstanceHandle instance, struct gnMacOSWindowSurfaceInfo_t createInfo) {
    windowSurface->windowSurface = malloc(sizeof(gnPlatformWindowSurface));
    windowSurface->windowSurface->layer = createInfo.layer;
    return GN_SUCCESS;
}

void gnDestroyWindowSurfaceFn(struct gnWindowSurface_t *windowSurface) {
    free(windowSurface->windowSurface);
}

struct gnSurfaceDetails_t gnGetSurfaceDetailsFn(
    struct gnWindowSurface_t* windowSurface, struct gnPhysicalDevice_t device
) {
    struct gnSurfaceDetails_t surfaceDetails;
    surfaceDetails.formatCount = 1;
    surfaceDetails.formats = (struct gnSurfaceFormat_t[1]){ { GN_FORMAT_BGRA8_SRGB, GN_COLOR_SPACE_SRGB_NONLINEAR } };
    surfaceDetails.minImageCount = 2;
    surfaceDetails.maxImageCount = 3;
    return surfaceDetails;
}

MTLPixelFormat mtlGryphnFormatToVulkanFormat(gnImageFormat format) {
    switch (format) {
    case GN_FORMAT_BGRA8_SRGB: { return MTLPixelFormatBGRA8Unorm_sRGB; }
    default: return MTLPixelFormatInvalid;
    }
}

CGColorSpaceRef mtlGryphnColorSpaceToVulkanColorSpace(gnColorSpace colorSpace) {
    switch (colorSpace) {
    case GN_COLOR_SPACE_SRGB_NONLINEAR: { return CGColorSpaceCreateWithName(kCGColorSpaceSRGB); }
    }
}
