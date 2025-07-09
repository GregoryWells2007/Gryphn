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

gnImageFormat mtlMetalFormatToGryphn(MTLPixelFormat format) {
    if (format == MTLPixelFormatBGRA8Unorm_sRGB) return GN_FORMAT_BGRA8_SRGB;
    return GN_FORMAT_NONE;
}

gnSurfaceDetails getMetalSurfaceDetails(
    gnWindowSurface windowSurface, gnPhysicalDevice device
) {
    gnSurfaceDetails surfaceDetails;
    surfaceDetails.formatCount = 1;
    surfaceDetails.formats = (gnSurfaceFormat[]){ { GN_FORMAT_BGRA8_SRGB, GN_COLOR_SPACE_SRGB_NONLINEAR } };
    surfaceDetails.minImageCount = 2;
    surfaceDetails.maxImageCount = 3;
    CGSize size = windowSurface->windowSurface->layer.drawableSize;
    surfaceDetails.minImageSize = surfaceDetails.maxImageSize = surfaceDetails.currentSize = (gnUInt2){size.width, size.height};
    return surfaceDetails;
}

MTLPixelFormat mtlGryphnFormatToMetalFormat(gnImageFormat format) {
    switch (format) {
    case GN_FORMAT_NONE: return MTLPixelFormatInvalid;
    case GN_FORMAT_BGRA8_SRGB: return MTLPixelFormatBGRA8Unorm_sRGB;
    case GN_FORMAT_BGRA8: return MTLPixelFormatBGRA8Unorm;
    case GN_FORMAT_RGBA8_SRGB: return MTLPixelFormatRGBA8Unorm_sRGB;
    case GN_FORMAT_D24S8_UINT: return MTLPixelFormatDepth24Unorm_Stencil8;
    case GN_FORMAT_D32S8_UINT: return MTLPixelFormatDepth32Float_Stencil8;
    }
}

CGColorSpaceRef mtlGryphnColorSpaceToMetalColorSpace(gnColorSpace colorSpace) {
    switch (colorSpace) {
    case GN_COLOR_SPACE_NONE: { return CGColorSpaceCreateWithName(kCGColorSpaceSRGB); } // very bad if here
    case GN_COLOR_SPACE_SRGB_NONLINEAR: { return CGColorSpaceCreateWithName(kCGColorSpaceSRGB); }
    }
}
