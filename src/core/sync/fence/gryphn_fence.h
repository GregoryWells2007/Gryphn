#pragma once
#include "core/gryphn_handles.h"
#include "utils/gryphn_bool.h"
#include "utils/gryphn_error_code.h"

#ifdef GN_REVEAL_IMPL
struct gnFence_t {
    struct gnPlatformFence_t* fence;
    gnOutputDeviceHandle device;
    gnBool signaled;
};
#endif

gnReturnCode gnCreateFence(gnFenceHandle* fence, gnOutputDeviceHandle device);
void gnSignalFence(gnFenceHandle fence);
void gnWaitForFence(gnFenceHandle fence, uint64_t timeout);
void gnResetFence(gnFenceHandle fence);
void gnDestroyFence(gnFenceHandle fence);
