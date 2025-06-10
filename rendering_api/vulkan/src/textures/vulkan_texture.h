#pragma once
#include <vulkan/vulkan.h>
#include "core/textures/gryphn_texture.h"
#include "buffers/vulkan_buffer.h"

typedef struct gnPlatformTexture_t {
    VkGryphnBuffer buffer;

    VkImage image;
    VkDeviceMemory memory;
    VkImageView imageView;
} gnPlatformTexture;
