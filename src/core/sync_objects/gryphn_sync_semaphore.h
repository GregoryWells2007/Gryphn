#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/output_device/gryphn_output_device.h"

struct gnPlatformSyncSemaphore;

struct gnSyncSemaphore {
ACCESS_LEVEL:
    gnPlatformSyncSemaphore* semaphore = nullptr;
public:
    gnSyncSemaphore() {}
};

inline gnReturnCode (*gnCreateSyncSemaphore)(gnSyncSemaphore* semaphore, const gnOutputDevice& device);
inline void (*gnDestroySyncSemaphore)(const gnSyncSemaphore& semaphore);
