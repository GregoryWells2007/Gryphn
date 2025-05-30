#pragma once
#include "core/output_device/gryphn_output_device.h"

typedef struct gnSemaphore_t {
    struct gnPlatformSemaphore_t* semaphore;
    struct gnOutputDevice_t* device;
} gnSemaphore;

gnReturnCode gnCreateSemaphore(struct gnSemaphore_t* semaphore, struct gnOutputDevice_t* device);
void gnDestroySemaphore(struct gnSemaphore_t* semaphore);
