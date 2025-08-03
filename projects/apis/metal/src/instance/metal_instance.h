#pragma once
#include <Metal/MTLRenderPipeline.h>
#include <AppKit/AppKit.h>
#include "core/src/instance/gryphn_instance.h"

typedef struct gnPlatformInstance_t {
    NSView* metalContentView;
} gnPlatformInstance;

gnReturnCode metalCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, PFN_gnCreateInstance_layer* next);
void metalDestroyInstance(gnInstance instance, PFN_gnDestroyInstance_layer* next);
