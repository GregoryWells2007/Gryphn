#pragma once
#include "command/command_pool/gryphn_command_pool.h"
#include <gryphn_handles.h>

GN_HANDLE(gnQueuedCommandPool);

typedef struct gnQueuedCommandPoolInfo {
    gnCommandPoolFlags flags;
    uint32_t queueFamilyIndex;
} gnQueuedCommandPoolInfo;

#ifdef GN_REVEAL_IMPL
struct gnQueuedCommandPool_t {
    struct gnPlatformCommandPool_t* commandPool;
    gnDevice device;
    gnInstance instance;
    gnCommandPoolInfo info;
};
#endif

gnReturnCode gnCreateQueuedCommandPool(gnQueuedCommandPool* commandPool, gnDeviceHandle device, gnQueuedCommandPoolInfo info);
void gnDestroyQueuedCommandPool(gnQueuedCommandPool commandPool);
