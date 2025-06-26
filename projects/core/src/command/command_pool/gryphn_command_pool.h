#pragma once
#include "stdint.h"
#include <utils/gryphn_error_code.h>
#include "gryphn_handles.h"

typedef struct gnCommandPoolInfo {
    uint32_t queueIndex;
} gnCommandPoolInfo;

#ifdef GN_REVEAL_IMPL
struct gnCommandPool_t {
    struct gnPlatformCommandPool_t* commandPool;
    gnDevice device;
    gnInstance instance;
};
#endif

gnReturnCode gnCreateCommandPool(gnCommandPoolHandle* commandPool, gnOutputDeviceHandle device, gnCommandPoolInfo info);
void gnDestroyCommandPool(gnCommandPoolHandle commandPool);
