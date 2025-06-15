#pragma once
#include <vulkan/vulkan.h>
#include "core/textures/gryphn_texture.h"
#include "buffers/vulkan_buffer.h"

typedef struct VkGryphnImage {
    VkImage image;
    VkDeviceMemory memory;
    VkImageView imageView;
} VkGryphnImage;
void gnDestroyVulkanImage(VkGryphnImage* image, VkDevice device);

typedef struct gnPlatformTexture_t {
    VkGryphnBuffer buffer;
    VkGryphnImage image;
    VkSampler sampler;

    size_t size;
    uint32_t width, height;
    gnBool beenWrittenToo;
} gnPlatformTexture;
