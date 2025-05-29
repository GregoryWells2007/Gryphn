#include "gryphn_command_pool.h"
#include "core/gryphn_platform_functions.h"

gnReturnCode gnCreateCommandPool(struct gnCommandPool_t* commandPool, struct gnOutputDevice_t* device, struct gnCommandPoolInfo_t info) {
    commandPool->device = device;
    return device->deviceFunctions->_gnCreateCommandPool(commandPool, device, info);
}

void gnDestroyCommandPool(struct gnCommandPool_t* commandPool) {
    commandPool->device->deviceFunctions->_gnDestroyCommandPool(commandPool);
}
