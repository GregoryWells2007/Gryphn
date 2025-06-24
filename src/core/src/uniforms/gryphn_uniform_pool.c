#include "gryphn_uniform_pool.h"
#include "output_device/gryphn_output_device.h"
#include "gryphn_platform_functions.h"
#include "gryphn_uniform.h"
#include "stdlib.h"

gnReturnCode gnCreateUniformPool(gnUniformPool* pool, gnDeviceHandle device) {
    *pool = malloc(sizeof(struct gnUniformPool_t));
    (*pool)->device = device;
    return device->deviceFunctions->_gnCreateUniformPool(*pool, device);
}

// you own this memory now
gnUniformArrayList gnUniformPoolAllocateUniforms(gnUniformPool pool, gnUniformAllocationInfo allocInfo) {
    gnUniform* uniforms = pool->device->deviceFunctions->_gnUniformPoolAllocateUniforms(pool, allocInfo);
    for (int i = 0; i < allocInfo.setCount; i++)
        uniforms[i]->pool = pool;

    gnUniformArrayList list = gnUniformArrayListCreate();
    gnUniformArrayListResize(&list, allocInfo.setCount);
    for (int i = 0; i < allocInfo.setCount; i++) list.data[i] = uniforms[i];
    return list;
}

void gnDestroyUniformPool(gnUniformPool pool) {
    pool->device->deviceFunctions->_gnDestroyUniformPool(pool);
}
