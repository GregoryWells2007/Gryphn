#include "gryphn_command_pool.h"
#include "gryphn_platform_functions.h"
#include "instance/init/gryphn_init.h"

gnReturnCode gnCreateCommandPool(gnCommandPoolHandle* commandPool, gnOutputDeviceHandle device, struct gnCommandPoolInfo_t info) {
    *commandPool = malloc(sizeof(struct gnCommandPool_t));
    if (!device->instance->loadCommandFunctions) {
        device->instance->commandFunctions = malloc(sizeof(struct gnCommandFunctions_t));
        gnLoadCommandFunctions(device->instance->dynamicLib, device->instance->commandFunctions);
        device->instance->loadCommandFunctions = gnTrue;
    }
    (*commandPool)->commandFunctions = device->instance->commandFunctions;

    (*commandPool)->device = device;
    return device->deviceFunctions->_gnCreateCommandPool((*commandPool), device, info);
}

void gnDestroyCommandPool(gnCommandPoolHandle commandPool) {
    commandPool->device->deviceFunctions->_gnDestroyCommandPool(commandPool);
}
