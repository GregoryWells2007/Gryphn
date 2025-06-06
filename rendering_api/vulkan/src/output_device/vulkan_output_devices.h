#pragma once
#include <vulkan/vulkan.h>
#include <core/output_device/gryphn_output_device.h>

typedef struct gnPlatformOutputDevice_t {
    VkDevice device;
    uint32_t queueCount;
    VkQueue* queues;

    VkQueue transferQueue;
    VkCommandPool transferCommandPool;
} gnPlatformOutputDevice;
