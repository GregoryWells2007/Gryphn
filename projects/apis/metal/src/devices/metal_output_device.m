#include <output_device/gryphn_physical_output_device.h>
#include <Metal/Metal.h>
#include "metal_output_devices.h"
#include "instance/metal_instance.h"
#include "instance/gryphn_instance.h"
#include <debugger/gryphn_debugger.h>

gnReturnCode createMetalOutputDevice(gnOutputDeviceHandle outputDevice, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo) {
    outputDevice->outputDevice = malloc(sizeof(gnPlatformOutputDevice));
    outputDevice->outputDevice->device = deviceInfo.physicalDevice.physicalDevice->device.retain;
    outputDevice->outputDevice->transferQueue = outputDevice->outputDevice->device.newCommandQueue;
    // outputDevice->outputDevice->queueCount = deviceInfo.queueInfoCount;
    // outputDevice->outputDevice->queues = malloc(sizeof(id<MTLCommandQueue>) * deviceInfo.queueInfoCount);
    // for (int i = 0; i < deviceInfo.queueInfoCount; i++) {
    //     outputDevice->outputDevice->queues[i] = outputDevice->outputDevice->device.newCommandQueue;
    // }

    return GN_SUCCESS;
}

void waitForMetalDevice(gnOutputDeviceHandle device) {
    [device->outputDevice->executingCommandBuffer waitUntilCompleted];
}

void destroyMetalOutputDevice(gnOutputDeviceHandle device) {
    // for (int i = 0; i < device->outputDevice->queueCount; i++) {
    //     [device->outputDevice->queues[i] release];
    // }
    [device->outputDevice->transferQueue release];
    [device->outputDevice->device release];
    free(device->outputDevice);
}

// struct mtlFramebufferVertex {
//     float x, y;
//     float u, v;
// };
