#include "gryphn_command_pool.h"
#include "stdlib.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"

gnReturnCode gnCreateCommandPool(gnCommandPoolHandle* commandPool, gnOutputDeviceHandle device, gnCommandPoolInfo info) {
    *commandPool = malloc(sizeof(struct gnCommandPool_t));
    (*commandPool)->instance = device->instance;

    (*commandPool)->device = device;
    return device->instance->callingLayer->deviceFunctions._gnCreateCommandPool((*commandPool), device, info);
}

void gnDestroyCommandPool(gnCommandPoolHandle commandPool) {
    commandPool->instance->callingLayer->deviceFunctions._gnDestroyCommandPool(commandPool);
}
