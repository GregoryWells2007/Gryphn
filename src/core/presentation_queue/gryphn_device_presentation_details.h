#pragma once
#include "../output_device/gryphn_physical_output_device.h"

struct gnDevicePresentationDetails {
public:
    int MinimumImageCount, MaximumImageCount;
};

inline gnDevicePresentationDetails (*gnGetDevicePresentationDetails)(const gnPhysicalOutputDevice& physicalOutputDevice);
