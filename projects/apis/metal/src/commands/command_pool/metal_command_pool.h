#pragma once
#import <Metal/Metal.h>
#include "command/command_pool/gryphn_command_pool.h"

typedef struct gnPlatformCommandPool_t {
    id<MTLCommandQueue> commandQueue;
} gnPlatformCommandPool;

gnReturnCode createMetalCommandPool(gnCommandPool commandPool, gnDevice device, gnCommandPoolInfo info);
void destroyMetalCommandPool(gnCommandPool commandPool);
