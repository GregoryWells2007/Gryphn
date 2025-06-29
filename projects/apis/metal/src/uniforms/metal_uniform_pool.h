#pragma once
#include <uniforms/gryphn_uniform_pool.h>

typedef struct gnPlatformUniformPool_t {} gnPlatformUniformPool;

gnReturnCode createMetalUniformPool(gnUniformPool pool, gnDeviceHandle device);
gnUniform* allocateMetalUniforms(gnUniformPool pool, const gnUniformAllocationInfo allocInfo);
void destroyMetalUniformPool(gnUniformPool pool);
