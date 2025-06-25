#include "metal_command_pool.h"
#include "devices/metal_output_devices.h"

gnReturnCode gnCreateCommandPoolFn(struct gnCommandPool_t* commandPool, struct gnOutputDevice_t* device, gnCommandPoolInfo info) {
    commandPool->commandPool = malloc(sizeof(struct gnPlatformCommandPool_t));
    commandPool->commandPool->commandQueue = [device->outputDevice->device newCommandQueue];

    return GN_SUCCESS;
}

void gnDestroyCommandPoolFn(struct gnCommandPool_t* commandPool) {
    [commandPool->commandPool->commandQueue release];
    free(commandPool->commandPool);
}
