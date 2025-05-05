#include <gryphn/gryphn_utils.h>
#include <vulkan/vulkan.h>
#include <core/sync_objects/gryphn_fence.h>

struct gnPlatformFence {
    VkFence fence;
    gnOutputDevice* device;
};
