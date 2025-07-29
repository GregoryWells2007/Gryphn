#pragma once
// #include "stdint.h"
#include <core/gryphn_return_code.h>
#include "gryphn_handles.h"

typedef enum gnCommandPoolFlagBits {
    GN_NO_FLAGS              = 0,
    GN_REUSE_COMMAND_BUFFERS = 1 << 0
} gnCommandPoolFlagBits;
typedef gnFlags gnCommandPoolFlags;

typedef struct gnCommandPoolInfo {
    gnCommandPoolFlags flags;
    uint32_t queueFamilyIndex; // ignored unless GN_EXT_QUEUES is enabled
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
