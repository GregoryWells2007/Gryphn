#include "vulkan_surface/vulkan_surface.h"
#include "vulkan_texture.h"
#include "output_device/vulkan_output_devices.h"
#include "output_device/vulkan_physical_device.h"
#include "core/debugger/gryphn_debugger.h"

VkImageType vkGryphnTextureType(gnTextureType type) {
switch(type) {
case GN_TEXTURE_2D: return VK_IMAGE_TYPE_3D;
}
}

void VkTransitionImageLayout(gnDevice device, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) {
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


        .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
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

void VkCopyBufferToImage(VkGryphnBuffer buffer, VkGryphnImage image, uint32_t width, uint32_t height, gnDevice device) {
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
            width,
            height,
            1
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

gnReturnCode gnCreateTextureFn(gnTexture texture, gnDevice device, const gnTextureInfo info) {
    texture->texture = malloc(sizeof(struct gnPlatformTexture_t));

    size_t imageSize = info.width * info.height;
    if (info.format == GN_FORMAT_BGRA8_SRGB) { imageSize *= 4; }

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
        .usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .extent = {
            .width = 100,
            .height = info.height,
            .depth = 1
        },
        .mipLevels = 1,
        .arrayLayers = 1,
        .imageType = vkGryphnTextureType(info.type),
        .format = vkGryphnFormatToVulkanFormat(info.format)
    };

    if (vkCreateImage(device->outputDevice->device, &imageInfo, NULL, &texture->texture->image.image) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_IMAGE;

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

    texture->texture->width = info.width;
    texture->texture->height = info.height;

    return GN_SUCCESS;
}

void gnTextureDataFn(gnTextureHandle texture, void* pixelData) {
    void* data;
    vkMapMemory(texture->device->outputDevice->device, texture->texture->buffer.memory, 0, texture->texture->size, 0, &data);
    memcpy(data, pixelData, texture->texture->size);
    vkUnmapMemory(texture->device->outputDevice->device, texture->texture->buffer.memory);

    if (texture->texture->beenWrittenToo) {
        gnDebuggerSetErrorMessage(texture->device->instance->debugger, (gnMessageData){
           .message = gnCreateString("this texture has alreay been written too with gnTextureData (vulkan) i need to implement the functionality to write to it multible times")
        });
    }

    //gnDevice device, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout
    VkTransitionImageLayout(texture->device, texture->texture->image.image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    VkCopyBufferToImage(texture->texture->buffer, texture->texture->image, texture->texture->width, texture->texture->height, texture->device);
    VkTransitionImageLayout(texture->device, texture->texture->image.image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    texture->texture->beenWrittenToo = gnTrue;
}

void gnDestroyVulkanImage(VkGryphnImage* image, VkDevice device) {
    vkDestroyImage(device, image->image, NULL);
    vkFreeMemory(device, image->memory, NULL);
}

void gnDestroyTextureFn(gnTexture texture) {
    gnDestroyVulkanBuffer(&texture->texture->buffer, texture->device->outputDevice->device);
    gnDestroyVulkanImage(&texture->texture->image, texture->device->outputDevice->device);
}
