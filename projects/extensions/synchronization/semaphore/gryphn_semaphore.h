#pragma once
#include "utils/gryphn_error_code.h"
#include "utils/lists/gryphn_array_list.h"
#include "gryphn_handles.h"

#ifdef GN_REVEAL_IMPL
struct gnSemaphore_t {
    struct gnPlatformSemaphore_t* semaphore;
    gnOutputDeviceHandle device;
};
#endif
GN_ARRAY_LIST(gnSemaphore);

gnReturnCode gnCreateSemaphore(gnSemaphore* semaphore, struct gnOutputDevice_t* device);
void gnDestroySemaphore(gnSemaphore semaphore);
