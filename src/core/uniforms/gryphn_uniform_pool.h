#pragma once
#include "core/gryphn_handles.h"
#include "utils/gryphn_error_code.h"
#include "core/uniforms/gryphn_uniform_layout.h"
#include "core/uniforms/gryphn_uniform.h"

#ifdef GN_REVEAL_IMPL
struct gnUniformPool_t {
    struct gnPlatformUniformPool_t* uniformPool;
    gnDeviceHandle device;
};
#endif

typedef struct gnUniformAllocationInfo {
    const uint32_t layoutCount;
    const gnUniformLayout* layouts;
} gnUniformAllocationInfo;

gnReturnCode gnCreateUniformPool(gnUniformPool* pool, gnDeviceHandle device);
gnUniformArrayList gnUniformPoolAllocateUniforms(gnUniformPool pool, gnUniformAllocationInfo allocInfo);
void gnDestroyUniformPool(gnUniformPool pool);
