#pragma once
#include <GL/gl.h>
#include "output_device/gryphn_physical_output_device.h"

typedef struct gnPlatformPhysicalDevice_t {} gnPlatformPhysicalDevice;

gnPhysicalDevice* getOpenGLDevice(gnInstanceHandle instance, uint32_t* deviceCount);
gnBool openglCanDevicePresent(gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface);
