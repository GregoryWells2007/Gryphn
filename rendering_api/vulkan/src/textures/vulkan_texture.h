#pragma once
#include <vulkan/vulkan.h>
#include "core/textures/gryphn_texture.h"

typedef struct gnPlatformTexture_t {
    VkImage image;
    VkImageView imageView;
} gnPlatformTexture;
