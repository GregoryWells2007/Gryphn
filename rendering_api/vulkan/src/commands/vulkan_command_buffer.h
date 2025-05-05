#pragma once
#include "core/graphics_pipeline/gryphn_graphics_pipeline.h"
#include <vulkan/vulkan.h>

struct gnPlatformCommandBuffer {
    VkCommandBuffer commandBuffer;

    gnOutputDevice* outputDevice;

    VkViewport viewport{};
    VkRect2D scissor{};
};

VkCommandBuffer beginSingleTimeCommands(const gnOutputDevice& outputDevice);
void endSingleTimeCommands(VkCommandBuffer commandBuffer, const gnOutputDevice& outputDevice);
