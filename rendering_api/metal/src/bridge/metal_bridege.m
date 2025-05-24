#include "metal_bridge.h"
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>

void mtlObjectCSetContentViewsLayer(void* view, void* layer) {
    [CATransaction begin];
    [CATransaction setDisableActions:YES];

    NSView* contentView = (__bridge NSView*)view;

    CAMetalLayer* metalLayer = (__bridge CAMetalLayer*)layer;

    [contentView setWantsLayer:YES];
    [contentView setLayer:metalLayer];

    [CATransaction commit];
}

void mtlInitializeMetalLayer(void* layer, gnBool vsync) {
    CAMetalLayer* metalLayer = (__bridge CAMetalLayer*)layer;
    metalLayer.maximumDrawableCount = 3;
    if (vsync == gnTrue)
        metalLayer.displaySyncEnabled = true;
    else
        metalLayer.displaySyncEnabled = false;
    metalLayer.framebufferOnly = true;
}
