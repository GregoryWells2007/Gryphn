#pragma once
#include <Metal/MTLRenderPipeline.h>
#include <AppKit/AppKit.h>
#include "core/src/instance/gryphn_instance.h"

typedef struct gnPlatformInstance_t {
    NSView* metalContentView;
} gnPlatformInstance;

gnReturnCode createMetalInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo);
void destroyMetalInstance(gnInstance instance);
