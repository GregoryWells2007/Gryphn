#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "core/src/gryphn_handles.h"

typedef struct gnQueueFamilyProperties gnQueueFamilyProperties;
typedef struct gnSubmitInfo gnSubmitInfo;
typedef struct gnSubmitSyncInfo gnSubmitSyncInfo;
typedef struct gnPresentInfo gnPresentInfo;
typedef struct gnPresentSyncInfo gnPresentSyncInfo;

typedef struct gnQueueExtFunctions {
    gnReturnCode (*_gnGetPhysicalDeviceQueueProperties)(gnPhysicalOutputDeviceHandle device, uint32_t queueCount, gnQueueFamilyProperties* queues);
    void (*_gnGetDeviceQueue)(gnOutputDevice device, uint32_t queueFamily, uint32_t queueIndex, gnQueue* queue);

    gnReturnCode (*_gnQueueSubmit)(gnOutputDevice device, gnQueue queue, gnSubmitInfo info);
    gnReturnCode (*_gnQueueSubmitSync)(gnOutputDevice device, gnQueue queue, gnSubmitSyncInfo info);

    gnReturnCode (*_gnQueuePresent)(gnDevice device, gnQueue queue, gnPresentInfo info);
    gnReturnCode (*_gnQueuePresentSync)(gnDevice device, gnQueue queue, gnPresentSyncInfo info);
} gnQueueExtFunctions;
