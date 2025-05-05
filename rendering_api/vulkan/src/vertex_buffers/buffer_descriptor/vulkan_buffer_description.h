#pragma once
#include "core/buffers/uniform_buffer_descriptor/gryphn_buffer_description.h"
#include <vulkan/vulkan.h>

struct gnPlatformBufferDescription {
    VkDescriptorSet descriptorSet;
    gnGraphicsPipeline* graphicsPipeline;
};
