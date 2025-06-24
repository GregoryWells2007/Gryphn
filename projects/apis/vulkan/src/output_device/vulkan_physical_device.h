#pragma once
#include <vulkan/vulkan.h>
#include <output_device/gryphn_physical_output_device.h>

typedef struct gnPlatformPhysicalDevice_t {
    VkPhysicalDevice device;
} gnPlatformPhysicalDevice;
