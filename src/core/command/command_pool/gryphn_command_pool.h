#pragma once
#include "stdint.h"
#include <core/output_device/gryphn_output_device.h>

typedef struct gnCommandPoolInfo_t {
    uint32_t queueIndex;
} gnCommandPoolInfo;

typedef struct gnCommandPool_t {
    struct gnPlatformCommandPool_t* commandPool;
    struct gnOutputDevice_t* device;
} gnCommandPool;

gnReturnCode gnCreateCommandPool(struct gnCommandPool_t* commandPool, struct gnOutputDevice_t* device, struct gnCommandPoolInfo_t info);
void gnDestroyCommandPool(struct gnCommandPool_t* commandPool);
