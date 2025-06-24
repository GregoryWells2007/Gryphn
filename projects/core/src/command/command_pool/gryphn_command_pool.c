#include "gryphn_command_pool.h"

gnReturnCode gnCreateCommandPool(gnCommandPoolHandle* commandPool, gnOutputDeviceHandle device, gnCommandPoolInfo info) {
    *commandPool = malloc(sizeof(struct gnCommandPool_t));
    (*commandPool)->commandFunctions = device->instance->commandFunctions;

    (*commandPool)->device = device;
    return device->deviceFunctions->_gnCreateCommandPool((*commandPool), device, info);
}

void gnDestroyCommandPool(gnCommandPoolHandle commandPool) {
    commandPool->device->deviceFunctions->_gnDestroyCommandPool(commandPool);
}
