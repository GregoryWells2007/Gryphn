#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <core/uniform_descriptor/gryphn_uniform.h>

struct gnOutputDevice;

struct gnPlatformUniform {
    VkDescriptorPool descriptorPool;
    gnOutputDevice* outputDevice;
    std::vector<VkDescriptorSet> descriptorSets;
};
