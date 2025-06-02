#pragma once
#include <utils/strings/gryphn_string.h>
#include <dlfcn.h>

#ifdef __OBJC__
@class NSWindow;
@class CAMetalLayer;
@class MTKView;
#else
typedef void NSWindow;
typedef void CAMetalLayer;
typedef void MTKView;
#endif

MTKView* gnCreateMTKView(NSWindow* window);
void gnWindowSetMTKView(NSWindow* window, MTKView* view);
CAMetalLayer* gnGetCAMetalLayer(NSWindow* window);

// CAMetalLayer* gnCreateMetalLayer(NSWindow* window);
// void gnAttachMetalLayer(NSWindow* window, CAMetalLayer* layer);
// void gnMetalLayerSetBounds(CAMetalLayer* layer, NSWindow* window);
// CAMetalLayer* gnGetMetalLayer(NSWindow* window);
