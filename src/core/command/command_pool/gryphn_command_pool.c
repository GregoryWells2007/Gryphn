#include "gryphn_command_pool.h"
#include "core/gryphn_platform_functions.h"
#include "core/instance/init/gryphn_init.h"

gnReturnCode gnCreateCommandPool(struct gnCommandPool_t* commandPool, struct gnOutputDevice_t* device, struct gnCommandPoolInfo_t info) {
    if (!device->instance->loadCommandFunctions) {
        device->instance->commandFunctions = malloc(sizeof(struct gnCommandFunctions_t));
        gnLoadCommandFunctions(device->instance->dynamicLib, device->instance->commandFunctions);
        device->instance->loadCommandFunctions = gnTrue;
    }
    commandPool->commandFunctions = device->instance->commandFunctions;

    commandPool->device = device;
    return device->deviceFunctions->_gnCreateCommandPool(commandPool, device, info);
}

void gnDestroyCommandPool(struct gnCommandPool_t* commandPool) {
    commandPool->device->deviceFunctions->_gnDestroyCommandPool(commandPool);
}
