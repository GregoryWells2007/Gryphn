#pragma once
#include "vulkan/vulkan.h"

struct gnPlatformVertexDescription {
    VkVertexInputBindingDescription bindingDescription{};
    VkVertexInputAttributeDescription* attributeDescriptions;

    uint32_t attributeDescriptionCount;
};
