#pragma once
#include <vulkan/vulkan.h>
#include "core/output_device/gryphn_output_device.h"

struct gnPlatformPhysicalOutputDevice {
    VkPhysicalDevice device;
    gnInstance* instance;
};

struct gnPlatformOutputDevice {
    VkDevice device;
    VkQueue presentQueue;
    VkQueue graphicsQueue;

    VkCommandPool commandPool;
};
