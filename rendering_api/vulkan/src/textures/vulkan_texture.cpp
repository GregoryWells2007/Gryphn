#include <vulkan/vulkan.h>
#include "gryphn/gryphn_utils.h"
#include "vulkan_texture.h"
#include "core/textures/gryphn_texture.h"
#include "../output_device/vulkan_output_devices.h"
#include "../vertex_buffers/vulkan_buffers.h"

void vulkanTexture(gnTexture* texture) {
    if (texture->texture == nullptr) texture->texture = new gnPlatformTexture();
}

gnReturnCode findDepthFormat(const gnOutputDevice& outputDevice, VkFormat& format) {
    return findSupportedFormat(outputDevice,
        {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT, format
    );
}

VkFormat vulkanFormatFromGryphnFormat(const gnOutputDevice& outputDevice, gnColorMode colorMode) {
    switch (colorMode) {
        case GN_RED: return VK_FORMAT_R8_UNORM;
        case GN_RGB8: return VK_FORMAT_R8G8B8A8_SRGB;
        case GN_RGBA8:  return VK_FORMAT_R8G8B8A8_SRGB;
        case GN_BGRA8:  return VK_FORMAT_B8G8R8A8_SRGB;
        case GN_DEPTH_STENCIL: {
            VkFormat depthFormat;
            findDepthFormat(outputDevice, depthFormat);
            return depthFormat;
        }
    }
    return VK_FORMAT_R8_UNORM;
}

GN_EXPORT void gnTextureDataFn(const gnTexture& texture, gnSize dataSize, const void* inputData) {
    texture.texture->size = dataSize;
    texture.texture->data = inputData;

    vulkanCreateBuffer(
            *texture.texture->outputDevice, texture.texture->size,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            texture.texture->stagingBuffer, texture.texture->stagingBufferMemory
    );

    void* data;
    vkMapMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBufferMemory, 0, texture.texture->size, 0, &data);
        memcpy(data, texture.texture->data, texture.texture->size);
    vkUnmapMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBufferMemory);

    VkFormat format = vulkanFormatFromGryphnFormat(*texture.texture->outputDevice, texture.textureColorFormat);

    transitionImageLayout(*texture.texture->outputDevice, texture.texture->textureImage, format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(*texture.texture->outputDevice, texture.texture->stagingBuffer, texture.texture->textureImage, texture.textureExtent.x, texture.textureExtent.y);
    transitionImageLayout(*texture.texture->outputDevice, texture.texture->textureImage, format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    vkDestroyBuffer(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBuffer, nullptr);
    vkFreeMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBufferMemory, nullptr);
}
GN_EXPORT void gnTextureCubeMapDataFn(const gnTexture& texture, gnSize imageDataSize, void* face1, void* face2, void* face3, void* face4, void* face5, void* face6) {
    texture.texture->size = imageDataSize;
    uint32_t faceSize = imageDataSize / 6;
    if (vulkanCreateBuffer(
            *texture.texture->outputDevice, texture.texture->size,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            texture.texture->stagingBuffer, texture.texture->stagingBufferMemory
    ) != GN_SUCCESS) {
        // return GN_FAILED;
    }

    void* data;
    vkMapMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBufferMemory, 0, texture.texture->size, 0, &data);

    memcpy((char*)data + (faceSize * 0), face1, faceSize);
    memcpy((char*)data + (faceSize * 1), face2, faceSize);
    memcpy((char*)data + (faceSize * 2), face3, faceSize);
    memcpy((char*)data + (faceSize * 3), face4, faceSize);
    memcpy((char*)data + (faceSize * 4), face5, faceSize);
    memcpy((char*)data + (faceSize * 5), face6, faceSize);

    vkUnmapMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBufferMemory);

    VkFormat format = vulkanFormatFromGryphnFormat(*texture.texture->outputDevice, texture.textureColorFormat);
    transitionImageLayout(*texture.texture->outputDevice, texture.texture->textureImage, format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 6);
    copyBufferToImage(*texture.texture->outputDevice, texture.texture->stagingBuffer, texture.texture->textureImage, texture.textureExtent.x, texture.textureExtent.y, 6);
    transitionImageLayout(*texture.texture->outputDevice, texture.texture->textureImage, format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, 6);

    vkDestroyBuffer(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBuffer, nullptr);
    vkFreeMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBufferMemory, nullptr);
}

void gnTextureSubData(const gnTexture& texture, gnSize offset, gnSize dataSize, void* inputData) {
    texture.texture->size = texture.dataSize;

    if (vulkanCreateBuffer(
            *texture.texture->outputDevice, texture.texture->size,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            texture.texture->stagingBuffer, texture.texture->stagingBufferMemory
    ) != GN_SUCCESS) {
        // return GN_FAILED;
    }

    void* data;
    vkMapMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBufferMemory, 0, texture.texture->size, 0, &data);
    memcpy((char*)data + offset, inputData, dataSize);
    vkUnmapMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBufferMemory);

    VkFormat format = vulkanFormatFromGryphnFormat(*texture.texture->outputDevice, texture.textureColorFormat);
    transitionImageLayout(*texture.texture->outputDevice, texture.texture->textureImage, format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(*texture.texture->outputDevice, texture.texture->stagingBuffer, texture.texture->textureImage, texture.textureExtent.x, texture.textureExtent.y);
    transitionImageLayout(*texture.texture->outputDevice, texture.texture->textureImage, format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    vkDestroyBuffer(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBuffer, nullptr);
    vkFreeMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->stagingBufferMemory, nullptr);
}

GN_EXPORT gnReturnCode gnCreateTextureFn(gnTexture* texture, const gnOutputDevice& outputDevice) {
    if (texture->texture == nullptr) texture->texture = new gnPlatformTexture();
    texture->texture->outputDevice = const_cast<gnOutputDevice*>(&outputDevice);

    // VkFormat textureFormat

    if (texture->textureType == GN_TEXTURE_2D) {
        if (texture->textureColorFormat == GN_RGBA8) {
            gnReturnCode res = vulkanCreateImage(outputDevice, texture->textureExtent.x, texture->textureExtent.y,
                VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                texture->texture->textureImage, texture->texture->textureImageMemory);
            if (res != GN_SUCCESS) return res;

            gnReturnCode errorCode = createImageView(outputDevice, texture->texture->textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, &texture->texture->textureImageView);
            if (errorCode != GN_SUCCESS) return errorCode;
        } else if (texture->textureColorFormat == GN_RGB8) {
            VkFormat textureFormat = VK_FORMAT_R8G8B8A8_SRGB;

            // if (formatSupported(outputDevice,
            //     VK_FORMAT_R8G8B8_SRGB,
            //     VK_IMAGE_TILING_OPTIMAL,
            //     VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
            // )) {
            //     textureFormat = VK_FORMAT_R8G8B8_SRGB;
            // }

            if (vulkanCreateImage(outputDevice, texture->textureExtent.x, texture->textureExtent.y,
                textureFormat, VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                texture->texture->textureImage, texture->texture->textureImageMemory) != GN_SUCCESS) {
                return GN_FAILED;
            }

            gnReturnCode errorCode = createImageView(outputDevice, texture->texture->textureImage, textureFormat, VK_IMAGE_ASPECT_COLOR_BIT, &texture->texture->textureImageView);
            if (errorCode != GN_SUCCESS) return errorCode;
        } else if (texture->textureColorFormat == GN_RED) {
            if (vulkanCreateImage(outputDevice, texture->textureExtent.x, texture->textureExtent.y,
                VK_FORMAT_R8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                texture->texture->textureImage, texture->texture->textureImageMemory) != GN_SUCCESS) {
                return GN_FAILED;
            }

            gnReturnCode errorCode = createImageView(outputDevice, texture->texture->textureImage, VK_FORMAT_R8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, &texture->texture->textureImageView);

            if (errorCode != GN_SUCCESS) return errorCode;
        }  else if (texture->textureColorFormat == GN_BGRA8) {
            if (vulkanCreateImage(outputDevice, texture->textureExtent.x, texture->textureExtent.y,
                VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                texture->texture->textureImage, texture->texture->textureImageMemory, VK_IMAGE_LAYOUT_UNDEFINED) != GN_SUCCESS) {
                return GN_FAILED;
            }

            gnReturnCode errorCode = createImageView(outputDevice, texture->texture->textureImage, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, &texture->texture->textureImageView);
            if (errorCode != GN_SUCCESS) return errorCode;
            //GN_ERROR_CODE code = transitionImageLayout(*texture.texture->outputDevice, texture.texture->textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

            gnReturnCode transitionErrorCode = transitionImageLayout(outputDevice, texture->texture->textureImage, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
            if (transitionErrorCode != GN_SUCCESS) return transitionErrorCode;
        } else if (texture->textureColorFormat == GN_DEPTH_STENCIL) {
            VkFormat depthFormat;
            gnReturnCode depthFormatReturnCode = findDepthFormat(outputDevice, depthFormat);
            if (depthFormatReturnCode != GN_SUCCESS) return depthFormatReturnCode;

            if (vulkanCreateImage(outputDevice, texture->textureExtent.x, texture->textureExtent.y,
                depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                texture->texture->textureImage, texture->texture->textureImageMemory) != GN_SUCCESS) {
                    return gnReturnError(GN_FAILED_TO_CREATE_IMAGE, "Failed to create depth image");
            }

            gnReturnCode errorCode = createImageView(outputDevice, texture->texture->textureImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, &texture->texture->textureImageView);
            if (transitionImageLayout(outputDevice, texture->texture->textureImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) != GN_SUCCESS) return gnReturnError(GN_FAILED_TO_CREATE_IMAGE, "Failed to transition image layout");
        }
    } else {
        if (vulkanCreateCubeMap(outputDevice, texture->textureExtent.x, texture->textureExtent.y, texture->texture->textureImage, texture->texture->textureImageMemory) != GN_SUCCESS)
            return GN_FAILED;
        if (vulkanCreateCubeMapImageView(outputDevice, texture->texture->textureImage, &texture->texture->textureImageView) != GN_SUCCESS)
            return GN_FAILED;
    }

    {
        VkSamplerCreateInfo samplerInfo{};
        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.magFilter = (texture->magFilter == GN_FILTER_LINEAR) ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
        samplerInfo.minFilter = (texture->minFilter == GN_FILTER_LINEAR) ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;

        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

        samplerInfo.anisotropyEnable = VK_TRUE;

        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(outputDevice.physicalOutputDevice->physicalOutputDevice->device, &properties);
        samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
        samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        samplerInfo.unnormalizedCoordinates = VK_FALSE;
        samplerInfo.compareEnable = VK_FALSE;
        samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerInfo.mipLodBias = 0.0f;
        samplerInfo.minLod = 0.0f;
        samplerInfo.maxLod = 0.0f;

        if (vkCreateSampler(outputDevice.outputDevice->device, &samplerInfo, nullptr, &texture->texture->textureSampler) != VK_SUCCESS)
            return gnReturnError(GN_FAILED_TO_CREATE_IMAGE, "Failed to create texture sampler");
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyTextureFn(const gnTexture& texture) {
    vkDestroySampler(texture.texture->outputDevice->outputDevice->device, texture.texture->textureSampler, nullptr);
    vkDestroyImageView(texture.texture->outputDevice->outputDevice->device, texture.texture->textureImageView, nullptr);

    vkDestroyImage(texture.texture->outputDevice->outputDevice->device, texture.texture->textureImage, nullptr);
    vkFreeMemory(texture.texture->outputDevice->outputDevice->device, texture.texture->textureImageMemory, nullptr);
}
