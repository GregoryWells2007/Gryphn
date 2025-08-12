#pragma once
#include <vulkan/vulkan.h>
#include "textures/gryphn_texture.h"
#include "buffers/vulkan_buffer.h"
#include "memory_allocator/vk_mem_alloc.h"

typedef struct VkGryphnImage {
    VkImage image;
    VmaAllocation allocation;
    VkImageView imageView;
} VkGryphnImage;
void gnDestroyVulkanImage(VkGryphnImage* image, gnDevice device);

typedef struct gnPlatformTexture_t {
    VkGryphnImage image;
    VkSampler sampler;
    size_t size;
    gnBool beenWrittenToo;

    VkImageLayout currentLayout;
} gnPlatformTexture;

gnReturnCode createTexture(gnTexture texture, gnDevice device, const gnTextureInfo info);
void textureData(gnTextureHandle texture, void* pixelData);
void destroyTexture(gnTexture texture);
