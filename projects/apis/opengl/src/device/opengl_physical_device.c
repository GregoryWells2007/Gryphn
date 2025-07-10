#include "opengl_physical_device.h"

gnPhysicalDevice* getOpenGLDevice(gnInstanceHandle instance, uint32_t* deviceCount) {
    *deviceCount = 1;

    gnPhysicalDevice* devices = malloc(sizeof(gnPhysicalDevice));

    gnPhysicalDevice device = {
        .physicalDevice = malloc(sizeof(gnPlatformPhysicalDevice)),
        .features = {
            .maxColorSamples = GN_SAMPLE_BIT_1,
            .maxDepthSamples = GN_SAMPLE_BIT_1,
            .maxMemoryAllocations = 0x40000000,
            .maxPushConstantSize = 256
        },
        .properties = {
            .deviceType = GN_DEDICATED_DEVICE,
            .name = gnCreateString("Generic OpenGL device")
        },
        .queueProperties = {
            .queueCount = 1,
            .queueProperties = (gnQueueProperties[1]){
                (gnQueueProperties){
                    .queueCount = 1,
                    .queueType = GN_QUEUE_GRAPHICS
                }
            }
        }
    };
    devices[0] = device;
    return devices;
}
gnBool openGLQueueCanPresent(const gnPhysicalDevice device, uint32_t queueIndex, gnWindowSurfaceHandle windowSurface) {
    return gnTrue;
}
