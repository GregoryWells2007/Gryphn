#include "vulkan_loader.h"
#include "extensions/queues/vulkan_device_queues.h"
#include <submit/vulkan_submit.h>
#include <present/vulkan_present.h>

gnQueueExtFunctions loadVulkanQueueFunctions(void) {
    return (gnQueueExtFunctions) {
        ._gnGetPhysicalDeviceQueueProperties = vulkanPhysicalDeviceQueueProperties,
        ._gnQueueSubmit = vulkanSubmitQueue,
        ._gnQueueSubmitSync = vulkanSubmitSyncQueue,
        ._gnGetDeviceQueue = getVulkanDeviceQueue,
        ._gnQueuePresent = vulkanQueuePresent,
        ._gnQueuePresentSync = vulkanQueuePresentSync
    };
}
