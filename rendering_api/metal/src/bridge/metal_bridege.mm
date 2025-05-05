#include "metal_bridge.h"
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

void mtlObjectCSetContentViewsLayer(void* window, void* layer) {
    [CATransaction begin];
    [CATransaction setDisableActions:YES];

    NSWindow* nsWindow = (NSWindow*)glfwGetCocoaWindow((GLFWwindow*)window);
    NSView* contentView = [nsWindow contentView];

    CAMetalLayer* metalLayer = (__bridge CAMetalLayer*)layer;

    [contentView setWantsLayer:YES];
    [contentView setLayer:metalLayer];

    [CATransaction commit];
}

void* mtlCreateContentView(void* targetWindow) {
    NSWindow* window = (__bridge NSWindow*)targetWindow;
    NSRect frame = [[window contentView] frame]; // fallback size
    NSView* contentView = [[NSView alloc] initWithFrame:frame];
    [window setContentView:contentView];

    if (contentView == nullptr)
        frame = NSMakeRect(0, 0, window.frame.size.width, window.frame.size.height);

    return contentView;
}

// void* mtlInitContentView(void* targetView) {
//     NSView* view = (__bridge NSView*)targetView;

//     CAMetalLayer* metalLayer = [CAMetalLayer layer];
//     // metalLayer.device = metalDevice;
//     metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
//     metalLayer.contentsScale = [view.window backingScaleFactor];
//     metalLayer.framebufferOnly = YES;
//     view.layer = metalLayer;
//     view.wantsLayer = YES;
//     return metalLayer;
// }

void mtlInitializeMetalLayer(void* layer, bool vsync) {
    CAMetalLayer* metalLayer = (__bridge CAMetalLayer*)layer;
    metalLayer.maximumDrawableCount = 3;
    metalLayer.displaySyncEnabled = vsync;
    metalLayer.framebufferOnly = true;
}
