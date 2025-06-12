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

gnReturnCode gnCreateUniformPool(gnUniformPool* pool, gnDeviceHandle device);
gnUniformArrayList gnUniformPoolAllocateUniforms(gnUniformPool pool, const gnUniformLayout layout);
void gnDestroyUniformPool(gnUniformPool pool);
