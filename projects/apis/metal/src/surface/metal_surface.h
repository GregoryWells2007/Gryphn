#pragma once
#include "window_surface/gryphn_surface.h"
#import <QuartzCore/QuartzCore.h>

typedef struct gnPlatformWindowSurface_t {
    CAMetalLayer* layer;
} gnPlatformWindowSurface;


MTLPixelFormat mtlGryphnFormatToMetalFormat(gnImageFormat format);
CGColorSpaceRef mtlGryphnColorSpaceToMetalColorSpace(gnColorSpace colorSpace);

gnReturnCode createMetalSurface(gnWindowSurface windowSurface, gnInstanceHandle instance, gnMacOSWindowSurfaceInfo createInfo);
gnSurfaceDetails getMetalSurfaceDetails(gnWindowSurface windowSurface, gnPhysicalDevice device);
void destroyMetalWindowSurface(gnWindowSurface windowSurface);
