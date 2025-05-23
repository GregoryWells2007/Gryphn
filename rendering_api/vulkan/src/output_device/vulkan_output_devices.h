#pragma once
#include <vulkan/vulkan.h>
#include <core/output_device/gryphn_output_device.h>

typedef struct gnPlatformOutputDevice_t {
    VkDevice device;
    VkQueue presentQueue;
    VkQueue graphicsQueue;
    // VkCommandPool commandPool;
} gnPlatformOutputDevice;
