#include "vulkan_loader.h"
#include "extensions/queues/vulkan_device_queues.h"
#include <submit/vulkan_submit.h>

gnQueueExtFunctions loadVulkanQueueFunctions() {
    return (gnQueueExtFunctions) {
        ._gnGetPhysicalDeviceQueueProperties = vulkanPhysicalDeviceQueueProperties,
        ._gnQueueSubmit = vulkanSubmitQueue,
        ._gnQueueSubmitSync = vulkanSubmitSyncQueue,
        ._gnGetDeviceQueue = getVulkanDeviceQueue
    };
}
