#include "gryphn_uniform_pool.h"
#include "core/output_device/gryphn_output_device.h"
#include "core/gryphn_platform_functions.h"
#include "stdlib.h"

gnReturnCode gnCreateUniformPool(gnUniformPool* pool, gnDeviceHandle device) {
    *pool = malloc(sizeof(struct gnUniformPool_t));
    (*pool)->device = device;
    return device->deviceFunctions->_gnCreateUniformPool(*pool, device);
}
