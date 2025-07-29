#pragma once
#include "core/gryphn_return_code.h"
#include "gryphn_handles.h"

typedef enum gnQueueTypeBits {
    GN_QUEUE_GRAPHICS_BIT       = 1 << 0,
    GN_QUEUE_COMPUTE_BIT        = 1 << 1,
    GN_QUEUE_TRANSFER_BIT       = 1 << 2,
    GN_QUEUE_SPARSE_BINDING_BIT = 1 << 3,
    GN_QUEUE_PROTECTED_BIT      = 1 << 4
} gnQueueTypeBits;
typedef gnFlags gnQueueTypeFlags;

typedef struct gnQueueFamilyProperties {
    uint32_t queueCount;
    gnQueueTypeFlags queueTypeFlags;
} gnQueueFamilyProperties;

gnReturnCode gnGetPhysicalDeviceQueueProperties(gnPhysicalOutputDeviceHandle device, uint32_t queueCount, gnQueueFamilyProperties* queues);
