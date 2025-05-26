#include "metal_surface.h"
#include "core/window_surface/gryphn_surface_create_functions.h"

#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>

gnReturnCode gnCreateMacOSWindowSurfaceFn(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnMacOSWindowSurfaceInfo_t createInfo) {
    NSWindow* window = (__bridge NSWindow*)createInfo.window;
    NSView* view = [window contentView];

    CAMetalLayer* layer = [CAMetalLayer layer];
    [layer setContentsScale:[window backingScaleFactor]];
    [layer setFramebufferOnly:YES];

    [view setLayer:layer];
    [view setWantsLayer:YES];

    windowSurface->windowSurface = malloc(sizeof(gnPlatformWindowSurface));
    return GN_SUCCESS;
}
