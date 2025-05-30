#pragma once
#include "core/output_device/gryphn_output_device.h"


typedef struct gnFence_t {
    struct gnPlatformFence_t* fence;
    struct gnOutputDevice_t* device;
    gnBool signaled;
} gnFence;

gnReturnCode gnCreateFence(struct gnFence_t* fence, struct gnOutputDevice_t* device);
void gnSignalFence(struct gnFence_t* fence);
void gnWaitForFence(struct gnFence_t* fence, uint64_t timeout);
void gnResetFence(struct gnFence_t* fence);
void gnDestroyFence(struct gnFence_t* fence);
