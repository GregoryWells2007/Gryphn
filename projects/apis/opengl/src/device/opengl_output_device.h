#pragma once
#include <output_device/gryphn_output_device.h>

typedef struct gnPlatformOutputDevice_t {} gnPlatformOutputDevice;

gnReturnCode createOpenGLOutputDevice(gnOutputDeviceHandle outputDevice, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo);
void waitForOpenGLDevice(const gnOutputDeviceHandle device);
void destroyOpenGLOutputDevice(gnOutputDeviceHandle device);
