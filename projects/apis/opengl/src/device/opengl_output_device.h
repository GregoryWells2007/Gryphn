#pragma once
#include <output_device/gryphn_output_device.h>

typedef struct gnPlatformOutputDevice_t {
    unsigned int buffer, shaderProgram;
} gnPlatformOutputDevice;

gnReturnCode createOpenGLOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle device, gnOutputDeviceInfo deviceInfo);
void waitForOpenGLDevice(const gnOutputDeviceHandle device);
void destroyOpenGLOutputDevice(gnOutputDeviceHandle device);
