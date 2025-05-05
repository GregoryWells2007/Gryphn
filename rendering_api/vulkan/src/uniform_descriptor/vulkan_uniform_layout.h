#pragma once
#include "gryphn/gryphn.h"
#include <vulkan/vulkan.h>

struct gnPlatformUniformLayout {
    gnOutputDevice* outputDevice;
    VkDescriptorSetLayout setLayout;
};

struct gnPlatformUniformLayoutBinding {
    // nothing here
};
