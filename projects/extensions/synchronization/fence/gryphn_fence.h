#pragma once
#include <utils/gryphn_bool.h>
#include "core/gryphn_return_code.h"
#include "utils/lists/gryphn_array_list.h"
#include "gryphn_handles.h"

#ifdef GN_REVEAL_IMPL
struct gnFence_t {
    struct gnPlatformFence_t* fence;
    gnOutputDeviceHandle device;
    gnBool signaled;
};
#endif
GN_ARRAY_LIST(gnFence);

gnReturnCode gnCreateFence(gnFenceHandle* fence, gnOutputDeviceHandle device);
void gnSignalFence(gnFenceHandle fence);
void gnWaitForFence(gnFenceHandle fence, uint64_t timeout);
void gnResetFence(gnFenceHandle fence);
void gnDestroyFence(gnFenceHandle fence);
