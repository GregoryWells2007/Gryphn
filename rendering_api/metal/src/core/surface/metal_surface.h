#pragma once
#include "core/window_surface/gryphn_surface.h"
#import <QuartzCore/QuartzCore.h>

typedef struct gnPlatformWindowSurface_t{
    CAMetalLayer* layer;
} gnPlatformWindowSurface;


MTLPixelFormat mtlGryphnFormatToVulkanFormat(gnImageFormat format);
CGColorSpaceRef mtlGryphnColorSpaceToVulkanColorSpace(gnColorSpace colorSpace);
