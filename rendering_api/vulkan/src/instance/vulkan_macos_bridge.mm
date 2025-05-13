#include "vulkan_macos_bridge.h"
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>

// kinda borrowed from cocoa_window.m in GLFW
void* macosBridge(void* inputWindow, void* inputView) {
    NSWindow* window = (__bridge NSWindow*)inputView;
    NSView* view = (__bridge NSView*)inputView;

    CAMetalLayer* layer = [CAMetalLayer layer];
    [layer setContentsScale:[window backingScaleFactor]];

    [view setLayer:layer];
    [view setWantsLayer:YES];
    return layer;
}
