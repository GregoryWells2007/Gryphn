#include "metal_surface.h"
#include "window_surface/gryphn_surface_create_functions.h"

#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>
#import <CoreGraphics/CoreGraphics.h>

gnReturnCode createMetalSurface(gnWindowSurface windowSurface, gnInstanceHandle instance, gnMacOSWindowSurfaceInfo createInfo) {
    windowSurface->windowSurface = malloc(sizeof(gnPlatformWindowSurface));
    windowSurface->windowSurface->layer = createInfo.layer;
    return GN_SUCCESS;
}

void destroyMetalWindowSurface(gnWindowSurface windowSurface) {
    free(windowSurface->windowSurface);
}

gnSurfaceDetails getMetalSurfaceDetails(
    gnWindowSurface windowSurface, gnPhysicalDevice device
) {
    gnSurfaceDetails surfaceDetails;
    surfaceDetails.formatCount = 1;
    surfaceDetails.formats = (gnSurfaceFormat[]){ { GN_FORMAT_BGRA8_SRGB, GN_COLOR_SPACE_SRGB_NONLINEAR } };
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
