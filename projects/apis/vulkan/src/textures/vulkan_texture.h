#pragma once
#include <vulkan/vulkan.h>
#include "textures/gryphn_texture.h"
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
    gnBool beenWrittenToo;
} gnPlatformTexture;

gnReturnCode createTexture(gnTexture texture, gnDevice device, const gnTextureInfo info);
void textureData(gnTextureHandle texture, void* pixelData);
void destroyTexture(gnTexture texture);
