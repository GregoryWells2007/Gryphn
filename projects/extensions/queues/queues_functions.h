#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "core/src/gryphn_handles.h"
#include "gryphn_queued_command_pool.h"

typedef struct gnQueueFamilyProperties gnQueueFamilyProperties;

typedef struct gnQueueExtFunctions {
    gnReturnCode (*_gnGetPhysicalDeviceQueueProperties)(gnPhysicalOutputDeviceHandle device, uint32_t queueCount, gnQueueFamilyProperties* queues);

    gnReturnCode (*_gnCreateQueuedCommandPool)(gnQueuedCommandPool* commandPool, gnDeviceHandle device, gnQueuedCommandPoolInfo info);
    void (*_gnDestroyQueuedCommandPool)(gnQueuedCommandPool commandPool);
} gnQueueExtFunctions;
