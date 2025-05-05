#include <vulkan/vulkan.h>
#include "core/output_device/gryphn_output_device.h"
#include <vulkan/vulkan_core.h>

struct gnPlatformShaderModule {
    VkShaderModule module;
    VkShaderEXT shader;
    VkPipelineShaderStageCreateInfo stageCreateInfo;
    const gnOutputDevice* device;
};
