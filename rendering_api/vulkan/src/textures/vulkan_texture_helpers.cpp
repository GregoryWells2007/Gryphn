#include <vulkan/vulkan.h>
#include "gryphn/gryphn_utils.h"
#include "vulkan_texture.h"
#include "core/textures/gryphn_texture.h"
#include "../vertex_buffers/vulkan_buffers.h"
#include "../output_device/vulkan_output_devices.h"
#include "../commands/vulkan_command_buffer.h"

void copyBufferToImage(const gnOutputDevice& outputDevice, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, int level_count) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(outputDevice);

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = level_count;

    region.imageOffset = {0, 0, 0};
    region.imageExtent = {
        width,
        height,
        1
    };

    vkCmdCopyBufferToImage(
        commandBuffer,
        buffer,
        image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        &region
    );

    endSingleTimeCommands(commandBuffer, outputDevice);
}

bool hasStencilComponent(VkFormat format) {
    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

gnReturnCode transitionImageLayout(const gnOutputDevice& outputDevice, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, int level_count) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(outputDevice);

    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = level_count;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }  else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    } else {
        return GN_FAILED;
    }

    if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

        if (hasStencilComponent(format)) {
            barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
        }
    } else {
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    }


    vkCmdPipelineBarrier(
        commandBuffer,
        sourceStage, destinationStage,
        0,
        0, nullptr,
        0, nullptr,
        1, &barrier
    );

    endSingleTimeCommands(commandBuffer, outputDevice);

    return GN_SUCCESS;
}

gnReturnCode vulkanCreateCubeMap(const gnOutputDevice& outputDevice, uint32_t width, uint32_t height, VkImage& image, VkDeviceMemory& imageMemory) {
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    imageInfo.mipLevels = 1;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.extent = { width, height, 1 };
    imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    imageInfo.arrayLayers = 6;
    imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT; // Optional

    if (vkCreateImage(outputDevice.outputDevice->device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
        return GN_FAILED;
    }

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(outputDevice.outputDevice->device, image, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;

    uint32_t memoryTypeIndex;
    if (findMemoryType(
        outputDevice.physicalOutputDevice->physicalOutputDevice->device,
        memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        &memoryTypeIndex) != GN_SUCCESS) {
            return GN_FAILED;
    }
    allocInfo.memoryTypeIndex = memoryTypeIndex;

    if (vkAllocateMemory(outputDevice.outputDevice->device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
        return GN_FAILED;
    }

    vkBindImageMemory(outputDevice.outputDevice->device, image, imageMemory, 0);

    return GN_SUCCESS;
}

gnReturnCode vulkanCreateImage(const gnOutputDevice& outputDevice,
    uint32_t width, uint32_t height,
    VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
    VkImage& image, VkDeviceMemory& imageMemory, VkImageLayout imageLayout
) {
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = static_cast<uint32_t>(width);
    imageInfo.extent.height = static_cast<uint32_t>(height);
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;

    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.initialLayout = imageLayout;
    imageInfo.usage = usage;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.flags = 0; // Optional

    VkResult result = vkCreateImage(outputDevice.outputDevice->device, &imageInfo, nullptr, &image);
    if (result != VK_SUCCESS) {
        GN_RETURN_ERROR(std::to_string(result).c_str());
    }

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(outputDevice.outputDevice->device, image, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;

    uint32_t memoryTypeIndex;
    if (findMemoryType(
        outputDevice.physicalOutputDevice->physicalOutputDevice->device,
        memRequirements.memoryTypeBits, properties,
        &memoryTypeIndex) != GN_SUCCESS) {
            GN_RETURN_ERROR("Failed to find memory type");
    }
    allocInfo.memoryTypeIndex = memoryTypeIndex;

    if (vkAllocateMemory(outputDevice.outputDevice->device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
        GN_RETURN_ERROR("Failed to allocate memory");
    }

    vkBindImageMemory(outputDevice.outputDevice->device, image, imageMemory, 0);

    return GN_SUCCESS;
}

gnReturnCode vulkanCreateImage(const gnOutputDevice& outputDevice,
    uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory
) {
    return vulkanCreateImage(outputDevice, width, height, format, tiling, usage, properties, image, imageMemory, VK_IMAGE_LAYOUT_UNDEFINED);
}

gnReturnCode vulkanCreateCubeMapImageView(const gnOutputDevice& outputDevice, VkImage image, VkImageView* imageView) {
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
    viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    viewInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    viewInfo.subresourceRange.layerCount = 6;
    viewInfo.subresourceRange.levelCount = 1;

    if (vkCreateImageView(outputDevice.outputDevice->device, &viewInfo, nullptr, imageView) != VK_SUCCESS) {
        return GN_FAILED;
    }

    return GN_SUCCESS;
}

gnReturnCode createImageView(const gnOutputDevice& outputDevice, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView* imageView) {
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    VkResult restult = vkCreateImageView(outputDevice.outputDevice->device, &viewInfo, nullptr, imageView);
    // std::cout << "Result:" << restult << "\n";
    if (restult != VK_SUCCESS) {
        return GN_FAILED;
    }

    return GN_SUCCESS;
}

gnReturnCode findSupportedFormat(const gnOutputDevice& outputDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkFormat& outFormat) {
    for (VkFormat format : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(outputDevice.physicalOutputDevice->physicalOutputDevice->device, format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
            outFormat = format;
            return GN_SUCCESS;
        } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
            outFormat = format;
            return GN_SUCCESS;
        }
    }

    return GN_FAILED;
}

bool formatSupported(const gnOutputDevice& outputDevice, const VkFormat format, VkImageTiling tiling, VkFormatFeatureFlags features) {
    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(outputDevice.physicalOutputDevice->physicalOutputDevice->device, format, &props);

    if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
        return true;
    } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
        return true;
    }
    return false;
}
