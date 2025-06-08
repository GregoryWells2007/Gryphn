#include "gryphn_uniform_pool.h"
#include "core/output_device/gryphn_output_device.h"
#include "core/gryphn_platform_functions.h"
#include "gryphn_uniform.h"
#include "stdlib.h"

gnReturnCode gnCreateUniformPool(gnUniformPool* pool, gnDeviceHandle device) {
    *pool = malloc(sizeof(struct gnUniformPool_t));
    (*pool)->device = device;
    return device->deviceFunctions->_gnCreateUniformPool(*pool, device);
}

// you own this memory now
gnUniform* gnUniformPoolAllocateUniforms(gnUniformPool pool, const gnUniformLayout layout) {
    gnUniform* uniforms = pool->device->deviceFunctions->_gnUniformPoolAllocateUniforms(pool, layout);
    for (int i = 0; i < layout.uniformBindingCount; i++)
        uniforms[i]->pool = pool;
    return uniforms;
}

void gnDestroyUniformPool(gnUniformPool pool) {
    pool->device->deviceFunctions->_gnDestroyUniformPool(pool);
}
