#pragma once
// theoretically you could have multible gryphn instances running in one application,
// why I dont know
#include "instance/gryphn_instance.h"
#include "debugger/gryphn_debugger.h"
#include "output_device/gryphn_physical_output_device.h"
#include "output_device/gryphn_output_device.h"

typedef struct gnFunctions_t {
    gnReturnCode (*_gnCreateInstance)(gnInstance* instance, struct gnInstanceInfo_t info);
    void (*_gnDestroyInstance)(gnInstance* instance);

    gnReturnCode (*_gnCreateDebugger)(gnDebugger* debugger, gnInstance* instance, const struct gnDebuggerInfo_t info);
    void (*_gnDestroyDebugger)(gnDebugger* debugger);

    gnBool (*_gnDeviceSupportsAPI)(const gnPhysicalDevice device);
    gnPhysicalDevice* (*_gnGetPhysicalDevices)(gnInstance* instance, uint32_t* count);

    gnReturnCode (*_gnRegisterOutputDevice)(gnOutputDevice* outputDevice, gnInstance* instance, const gnPhysicalDevice physicalDevice);
    void (*_gnDestroyOutputDevice)(gnOutputDevice* device);
} gnFunctions;

typedef struct gnDeviceFunctions_t {

} gnDeviceFunctions;
