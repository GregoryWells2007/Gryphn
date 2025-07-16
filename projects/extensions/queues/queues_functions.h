#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "core/src/gryphn_handles.h"

typedef struct gnQueueFamilyProperties gnQueueFamilyProperties;

typedef struct gnQueueExtFunctions {
    gnReturnCode (*_gnGetPhysicalDeviceQueueProperties)(gnPhysicalOutputDeviceHandle device, uint32_t queueCount, gnQueueFamilyProperties* queues);
    void (*_gnGetDeviceQueue)(gnOutputDevice device, uint32_t queueFamily, uint32_t queueIndex, gnQueue* queue);
} gnQueueExtFunctions;
