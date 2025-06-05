#pragma once
#include "stdint.h"
#include <utils/gryphn_error_code.h>
#include "core/gryphn_handles.h"

typedef struct gnCommandPoolInfo_t {
    uint32_t queueIndex;
} gnCommandPoolInfo;

#ifdef GN_REVEAL_IMPL
struct gnCommandPool_t {
    struct gnPlatformCommandPool_t* commandPool;
    struct gnCommandFunctions_t* commandFunctions;
    struct gnOutputDevice_t* device;
};
#endif

gnReturnCode gnCreateCommandPool(gnCommandPoolHandle* commandPool, gnOutputDeviceHandle device, struct gnCommandPoolInfo_t info);
void gnDestroyCommandPool(gnCommandPoolHandle commandPool);
