#pragma once
#include "stdint.h"
#include <utils/gryphn_error_code.h>
#include "gryphn_handles.h"

typedef enum gnCommandPoolFlags {
    GN_NO_FLAGS = 0,
    GN_REUSE_COMMAND_BUFFERS = 1
} gnCommandPoolFlags;

typedef struct gnCommandPoolInfo {
    uint32_t queueIndex;
    gnCommandPoolFlags flags;
} gnCommandPoolInfo;

#ifdef GN_REVEAL_IMPL
struct gnCommandPool_t {
    struct gnPlatformCommandPool_t* commandPool;
    gnDevice device;
    gnInstance instance;
    gnCommandPoolInfo info;
};
#endif

gnReturnCode gnCreateCommandPool(gnCommandPoolHandle* commandPool, gnOutputDeviceHandle device, gnCommandPoolInfo info);
void gnDestroyCommandPool(gnCommandPoolHandle commandPool);
