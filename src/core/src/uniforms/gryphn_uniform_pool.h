#pragma once
#include "utils/gryphn_error_code.h"
#include "uniforms/gryphn_uniform_layout.h"
#include "uniforms/gryphn_uniform.h"
#include "gryphn_handles.h"

#ifdef GN_REVEAL_IMPL
struct gnUniformPool_t {
    struct gnPlatformUniformPool_t* uniformPool;
    gnDeviceHandle device;
};
#endif

typedef struct gnUniformAllocationInfo {
    const uint32_t setCount;
    const gnUniformSet* sets;
} gnUniformAllocationInfo;

gnReturnCode gnCreateUniformPool(gnUniformPool* pool, gnDeviceHandle device);
gnUniformArrayList gnUniformPoolAllocateUniforms(gnUniformPool pool, gnUniformAllocationInfo allocInfo);
void gnDestroyUniformPool(gnUniformPool pool);
