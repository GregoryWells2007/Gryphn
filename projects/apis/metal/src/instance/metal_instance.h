#pragma once
#include <Metal/MTLRenderPipeline.h>
#include <AppKit/AppKit.h>
#include "core/src/instance/gryphn_instance.h"

typedef struct gnPlatformInstance_t {
    NSView* metalContentView;
} gnPlatformInstance;

gnReturnCode metalCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, gryphnInstanceFunctionLayers* next, gnAllocators* allocators);
void metalDestroyInstance(gnInstance instance, gryphnInstanceFunctionLayers* next, gnAllocators* allocators);
