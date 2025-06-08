#pragma once
#include "core/gryphn_handles.h"
#include "utils/gryphn_error_code.h"

#ifdef GN_REVEAL_IMPL
struct gnUniformPool_t {
    struct gnPlatformUniformPool_t* uniformPool;
    gnDeviceHandle device;
};
#endif

gnReturnCode gnCreateUniformPool(gnUniformPool* pool, gnDeviceHandle device);
// void gnUniformPoolAllocateUniforms
