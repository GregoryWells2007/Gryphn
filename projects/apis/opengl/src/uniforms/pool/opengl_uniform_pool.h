#pragma once
#include "core/src/uniforms/gryphn_uniform_pool.h"

typedef struct gnPlatformUniformPool_t { gnBool warningAvoider; } gnPlatformUniformPool;
gnReturnCode openglCreateUniformPool(gnUniformPool pool, gnDeviceHandle device);
gnUniform* openglAllocateUniforms(gnUniformPool pool, const gnUniformAllocationInfo allocInfo);
void openglDestroyUniformPool(gnUniformPool pool);
