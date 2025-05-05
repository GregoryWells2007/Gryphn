#pragma once
#include <vulkan/vulkan.h>
#include "gryphn/gryphn_utils.h"

struct gnOutputDevice;

struct gnPlatformTexture {
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    VkImage textureImage;
    VkImageView textureImageView;
    VkDeviceMemory textureImageMemory;
    VkSampler textureSampler;

    gnSize size;
    const void* data;

    gnOutputDevice* outputDevice;

    bool swapchainImage = false;
};

gnReturnCode vulkanCreateImage(const gnOutputDevice& device,
    uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory
);
gnReturnCode vulkanCreateImage(const gnOutputDevice& device,
    uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory, VkImageLayout imageLayout
);
gnReturnCode vulkanCreateCubeMap(const gnOutputDevice& device, uint32_t width, uint32_t height, VkImage& image, VkDeviceMemory& imageMemory);
gnReturnCode vulkanCreateCubeMapImageView(const gnOutputDevice& outputDevice, VkImage image, VkImageView* imageView);

gnReturnCode createImageView(const gnOutputDevice& outputDevice, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView* imageView);
gnReturnCode findSupportedFormat(const gnOutputDevice& outputDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkFormat& outFormat);
gnReturnCode transitionImageLayout(const gnOutputDevice& outputDevice, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, int level_count = 1);
void copyBufferToImage(const gnOutputDevice& outputDevice, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, int level_count = 1);
gnReturnCode findDepthFormat(const gnOutputDevice& outputDevice, VkFormat& format);
bool formatSupported(const gnOutputDevice& outputDevice, const VkFormat format, VkImageTiling tiling, VkFormatFeatureFlags features);
