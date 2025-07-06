#include "vulkan_surface/vulkan_surface.h"
#include "vulkan_texture.h"
#include "output_device/vulkan_output_devices.h"
#include "output_device/vulkan_physical_device.h"

VkImageType vkGryphnTextureType(gnTextureType type) {
    switch(type) {
        case GN_TEXTURE_2D: return VK_IMAGE_TYPE_2D;
    }
}

VkImageViewType vkGryphnTextureTypeView(gnTextureType type) {
    switch(type) {
        case GN_TEXTURE_2D: return VK_IMAGE_VIEW_TYPE_2D;
    }
}

VkSamplerAddressMode vkGryphnTextureWrap(gnTextureWrap wrap) {
    switch(wrap) {
        case GN_REPEAT: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
        case GN_MIRRORED_REPEAT: return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
        case GN_CLAMP_TO_EDGE: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        case GN_CLAMP_TO_BORDER: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
    }
}

VkImageUsageFlags gnImageUsageToVulkan(gnTextureUsageFlags flags) {
    VkImageUsageFlags vkFlags = 0;

    if ((flags & GN_TEXTURE_USAGE_COLOR_ATTACHMENT) == GN_TEXTURE_USAGE_COLOR_ATTACHMENT) vkFlags |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if ((flags & GN_TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT) == GN_TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT) vkFlags |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if ((flags & GN_TEXTURE_USAGE_SAMPLED) == GN_TEXTURE_USAGE_SAMPLED) vkFlags |= VK_IMAGE_USAGE_SAMPLED_BIT;
    if ((flags & GN_TEXTURE_USAGE_WRITE_TARGET) == GN_TEXTURE_USAGE_WRITE_TARGET) vkFlags |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    if ((flags & GN_TEXTURE_RESOLVE_ATTACHMENT) == GN_TEXTURE_RESOLVE_ATTACHMENT) vkFlags |= VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;

    return vkFlags;
}

VkImageAspectFlags vkGryphnGetAspectFlags(gnImageFormat format) {
    VkImageAspectFlags aspectMask = 0;

    if (format == GN_FORMAT_D32S8_UINT || format == GN_FORMAT_D24S8_UINT) aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
    else { aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; }

    return aspectMask;
}

gnBool vkGryphnIsDepthStencil(gnImageFormat format) { return (format == GN_FORMAT_D32S8_UINT || format == GN_FORMAT_D24S8_UINT); }



void VkTransitionImageLayout(gnDevice device, VkImage image, gnImageFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) {
    VkCommandBuffer transferBuffer = gnBeginVulkanTransferOperation(device);

    VkPipelineStageFlags sourceStage, destinationStage;
    VkAccessFlags sourceAccessMask, destinationAccessMask;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        sourceAccessMask = 0;
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

        destinationAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        sourceAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;

        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        destinationAccessMask = VK_ACCESS_SHADER_READ_BIT;
    } else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
       sourceAccessMask = 0;
       sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

       destinationAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
       destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
   }

    VkImageMemoryBarrier barrier = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .image = image,

        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .srcAccessMask = sourceAccessMask,
        .oldLayout = oldLayout,

        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstAccessMask = destinationAccessMask,
        .newLayout = newLayout,


        .subresourceRange.aspectMask = vkGryphnGetAspectFlags(format),
        .subresourceRange.baseMipLevel = 0,
        .subresourceRange.levelCount = 1,
        .subresourceRange.baseArrayLayer = 0,
        .subresourceRange.layerCount = 1,

    };

    vkCmdPipelineBarrier(
        transferBuffer,
        sourceStage, destinationStage,
        0,
        0, NULL,
        0, NULL,
        1, &barrier
    );

    gnEndVulkanTransferOperation(device, transferBuffer);
}

void VkCopyBufferToImage(VkGryphnBuffer buffer, VkGryphnImage image, gnExtent3D extent, gnDevice device) {
    VkCommandBuffer transferBuffer = gnBeginVulkanTransferOperation(device);

    VkBufferImageCopy region = {
        .bufferOffset = 0,
        .bufferRowLength = 0,
        .bufferImageHeight = 0,

        .imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .imageSubresource.mipLevel = 0,
        .imageSubresource.baseArrayLayer = 0,
        .imageSubresource.layerCount = 1,

        .imageOffset = (VkOffset3D){0, 0, 0},
        .imageExtent = (VkExtent3D){
            extent.width,
            extent.height,
            extent.depth
        }
    };

    vkCmdCopyBufferToImage(
        transferBuffer,
        buffer.buffer, image.image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1, &region
    );

    gnEndVulkanTransferOperation(device, transferBuffer);
}

gnReturnCode createTexture(gnTexture texture, gnDevice device, const gnTextureInfo info) {
    texture->texture = malloc(sizeof(struct gnPlatformTexture_t));

    size_t imageSize = info.extent.width * info.extent.height;
    if (info.format == GN_FORMAT_BGRA8_SRGB) { imageSize *= 4; }
    if (info.format == GN_FORMAT_RGBA8_SRGB) { imageSize *= 4; }

    gnReturnCode staginBufferCreateCode = VkCreateBuffer(
        &texture->texture->buffer, imageSize, device,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, VK_BUFFER_USAGE_TRANSFER_SRC_BIT
    );
    if (staginBufferCreateCode != GN_SUCCESS) return GN_FAILED_TO_CREATE_BUFFER;
    texture->texture->size = imageSize;

    VkImageCreateInfo imageInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .samples = gnSampleCountToVulkan(info.samples),
        .usage = gnImageUsageToVulkan(info.usage),
        .extent = {
            .width = info.extent.width,
            .height = info.extent.height,
            .depth = info.extent.depth
        },
        .mipLevels = 1,
        .arrayLayers = 1,
        .imageType = vkGryphnTextureType(info.type),
        .format = vkGryphnFormatToVulkanFormat(info.format)
    };

    VkResult res = vkCreateImage(device->outputDevice->device, &imageInfo, NULL, &texture->texture->image.image);
    if (res == VK_ERROR_FORMAT_NOT_SUPPORTED) return GN_UNSUPPORTED_IMAGE_FORMAT;
    else if (res != VK_SUCCESS) return GN_FAILED_TO_CREATE_IMAGE;

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device->outputDevice->device, texture->texture->image.image, &memRequirements);

    gnBool foundMemory = gnFalse;
    VkMemoryAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memRequirements.size,
        .memoryTypeIndex = VkMemoryIndex(device->physicalDevice.physicalDevice->device, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &foundMemory)
    };
    if (!foundMemory) return GN_FAILED_TO_ALLOCATE_MEMORY;

    if (vkAllocateMemory(device->outputDevice->device, &allocInfo, NULL, &texture->texture->image.memory) != VK_SUCCESS)
        return GN_FAILED_TO_ALLOCATE_MEMORY;

    vkBindImageMemory(device->outputDevice->device, texture->texture->image.image, texture->texture->image.memory, 0);

    texture->texture->beenWrittenToo = gnFalse;

    VkImageViewCreateInfo viewInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = texture->texture->image.image,
        .viewType = vkGryphnTextureTypeView(info.type),
        .format = vkGryphnFormatToVulkanFormat(info.format),

        .subresourceRange.aspectMask = vkGryphnGetAspectFlags(info.format),
        .subresourceRange.baseMipLevel = 0,
        .subresourceRange.levelCount = 1,
        .subresourceRange.baseArrayLayer = 0,
        .subresourceRange.layerCount = 1,
    };

    if (vkCreateImageView(device->outputDevice->device, &viewInfo, NULL, &texture->texture->image.imageView) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_IMAGE_VIEW;

    VkPhysicalDeviceProperties properties = {};
    vkGetPhysicalDeviceProperties(device->physicalDevice.physicalDevice->device, &properties);

    VkSamplerCreateInfo samplerInfo = {
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .minFilter = (info.minFilter == GN_FILTER_LINEAR) ? VK_FILTER_LINEAR : VK_FILTER_NEAREST,
        .magFilter = (info.magFilter == GN_FILTER_LINEAR) ? VK_FILTER_LINEAR : VK_FILTER_NEAREST,

        .addressModeU = vkGryphnTextureWrap(info.wrapU),
        .addressModeV = vkGryphnTextureWrap(info.wrapV),
        .addressModeW = vkGryphnTextureWrap(info.wrapW),

        .anisotropyEnable = VK_TRUE,
        .maxAnisotropy = properties.limits.maxSamplerAnisotropy,
        .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
        .unnormalizedCoordinates = VK_FALSE,

        .compareEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_ALWAYS,

        .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
        .mipLodBias = 0.0f,
        .minLod = 0.0f,
        .maxLod = 0.0f,
    };

    if (vkCreateSampler(device->outputDevice->device, &samplerInfo, NULL, &texture->texture->sampler) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_SAMPLER;

    if (vkGryphnIsDepthStencil(info.format))
        VkTransitionImageLayout(texture->device, texture->texture->image.image, texture->info.format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

    return GN_SUCCESS;
}

void textureData(gnTextureHandle texture, void* pixelData) {
    void* data;
    vkMapMemory(texture->device->outputDevice->device, texture->texture->buffer.memory, 0, texture->texture->size, 0, &data);
    memcpy(data, pixelData, texture->texture->size);
    vkUnmapMemory(texture->device->outputDevice->device, texture->texture->buffer.memory);

    //gnDevice device, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout
    VkTransitionImageLayout(texture->device, texture->texture->image.image, texture->info.format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    VkCopyBufferToImage(texture->texture->buffer, texture->texture->image, texture->info.extent, texture->device);
    VkTransitionImageLayout(texture->device, texture->texture->image.image, texture->info.format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    texture->texture->beenWrittenToo = gnTrue;
}

void gnDestroyVulkanImage(VkGryphnImage* image, VkDevice device) {
    vkDestroyImage(device, image->image, NULL);
    vkDestroyImageView(device, image->imageView, NULL);
    vkFreeMemory(device, image->memory, NULL);
}

void destroyTexture(gnTexture texture) {
    vkDestroySampler(texture->device->outputDevice->device, texture->texture->sampler, NULL);

    gnDestroyVulkanBuffer(&texture->texture->buffer, texture->device->outputDevice->device);
    gnDestroyVulkanImage(&texture->texture->image, texture->device->outputDevice->device);
}
