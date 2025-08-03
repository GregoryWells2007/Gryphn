#include "metal_command_pool.h"
#include "devices/metal_output_devices.h"

gnReturnCode createMetalCommandPool(gnCommandPool commandPool, gnDevice device, gnCommandPoolInfo info) {
    info.flags = 0;
    commandPool->commandPool = malloc(sizeof(struct gnPlatformCommandPool_t));
    commandPool->commandPool->commandQueue = [device->outputDevice->device newCommandQueue];

    return GN_SUCCESS;
}

void destroyMetalCommandPool(gnCommandPool commandPool) {
    [commandPool->commandPool->commandQueue release];
    free(commandPool->commandPool);
}
