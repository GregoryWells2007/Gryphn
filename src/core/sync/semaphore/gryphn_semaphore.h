#pragma once
#include "core/gryphn_handles.h"
#include "utils/gryphn_error_code.h"

#ifdef GN_REVEAL_IMPL
struct gnSemaphore_t {
    struct gnPlatformSemaphore_t* semaphore;
    gnOutputDeviceHandle device;
};
#endif

gnReturnCode gnCreateSemaphore(gnSemaphore* semaphore, struct gnOutputDevice_t* device);
void gnDestroySemaphore(gnSemaphore semaphore);
