#pragma once
#import <Metal/Metal.h>
#include "core/command/command_pool/gryphn_command_pool.h"

typedef struct gnPlatformCommandPool_t {
    id<MTLCommandQueue> commandQueue;
} gnPlatformCommandPool;
