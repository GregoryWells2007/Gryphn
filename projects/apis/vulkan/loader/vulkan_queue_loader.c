#include "vulkan_loader.h"
#include "extensions/queues/vulkan_device_queues.h"

gnQueueExtFunctions loadVulkanQueueFunctions() {
    return (gnQueueExtFunctions) {
        ._gnGetPhysicalDeviceQueueProperties = vulkanPhysicalDeviceQueueProperties
    };
}
