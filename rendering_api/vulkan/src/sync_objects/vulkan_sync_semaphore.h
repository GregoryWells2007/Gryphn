#include <gryphn/gryphn_utils.h>
#include <vulkan/vulkan.h>
#include "../output_device/vulkan_output_devices.h"
#include "core/sync_objects/gryphn_sync_semaphore.h"

struct gnPlatformSyncSemaphore {
    VkSemaphore semaphore;
    gnOutputDevice* device;
};
