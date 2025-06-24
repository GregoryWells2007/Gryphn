#pragma once
#include <vulkan/vulkan.h>
#include <core/output_device/gryphn_physical_output_device.h>

typedef struct gnPlatformPhysicalDevice_t {
    VkPhysicalDevice device;
} gnPlatformPhysicalDevice;
