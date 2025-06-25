#pragma once
#include <utils/gryphn_string.h>
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

// MTKView* gnCreateMTKView(NSWindow* window);
// void gnWindowSetMTKView(NSWindow* window, MTKView* view);
CAMetalLayer* gnCreateCAMetalLayer(NSWindow* window);
// CAMetalLayer* gnGetCAMetalLayer(NSWindow* window);
// void gnAttachMetalLayer(NSWindow* window, CAMetalLayer* layer);

// CAMetalLayer* gnCreateMetalLayer(NSWindow* window);
// void gnAttachMetalLayer(NSWindow* window, CAMetalLayer* layer);
// void gnMetalLayerSetBounds(CAMetalLayer* layer, NSWindow* window);
// CAMetalLayer* gnGetMetalLayer(NSWindow* window);
