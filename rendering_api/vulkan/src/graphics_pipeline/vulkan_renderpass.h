#pragma once
#include "vulkan/vulkan.h"
#include "../output_device/vulkan_output_devices.h"

struct gnPlatformSubpass {
    VkSubpassDescription subpass{};
    VkSubpassDependency dependency{};
};

struct gnPlatformRenderPass {
    VkRenderPass renderPass;
    gnOutputDevice* outputDevice;
};

struct gnPlatformRenderPassFrame {
    VkRenderPassBeginInfo renderPassInfo{};
};
