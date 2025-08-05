#include "opengl_physical_device.h"
#include "stdlib.h"

gnPhysicalDevice* getOpenGLDevice(gnInstanceHandle instance, uint32_t* deviceCount) {
    *deviceCount = 1;

    gnPhysicalDevice* devices = malloc(sizeof(gnPhysicalDevice));
    devices[0] = malloc(sizeof(struct gnPhysicalOutputDevice_t));
    *devices[0] = (struct gnPhysicalOutputDevice_t){
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
        }
    };
    return devices;
}
gnBool openglCanDevicePresent(gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface) {
    return GN_TRUE;
}
