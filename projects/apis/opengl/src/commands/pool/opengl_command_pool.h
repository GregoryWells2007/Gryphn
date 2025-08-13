#pragma once
#include "core/src/command/command_pool/gryphn_command_pool.h"

typedef struct gnPlatformCommandPool_t gnPlatformCommandPool;
gnReturnCode openglCreateCommandPool(gnCommandPool commandPool, gnDevice device, gnCommandPoolInfo info);
void openglDestroyCommandPool(gnCommandPool commandPool);
