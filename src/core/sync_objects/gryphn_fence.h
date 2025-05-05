#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/output_device/gryphn_output_device.h"

struct gnPlatformFence;

struct gnFence {
ACCESS_LEVEL:
    gnPlatformFence* fence = nullptr;
public:
    gnFence() {}
};

inline gnReturnCode (*gnCreateFence)(gnFence* fence, const gnOutputDevice& device);
inline void (*gnWaitForFence)(const gnFence& fence);
inline void (*gnResetFence)(gnFence& fence);
inline void (*gnDestroyFence)(gnFence& fence);
