#include "vulkan_surface/vulkan_surface.h"
#include "vulkan_texture.h"
#include "output_device/vulkan_output_devices.h"

VkImageType vkGryphnTextureType(gnTextureType type) {
switch(type) {
case GN_TEXTURE_2D: return VK_IMAGE_TYPE_3D;
}
}

gnReturnCode gnCreateTextureFn(gnTexture texture, gnDevice device, const gnTextureInfo info) {
    texture->texture = malloc(sizeof(struct gnPlatformTexture_t));

    VkImageCreateInfo imageInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .extent = {
            .width = info.width,
            .height = info.height,
            .depth = 1
        },
        .mipLevels = 1,
        .arrayLayers = 1,
        .imageType = vkGryphnTextureType(info.type),
        .format = vkGryphnFormatToVulkanFormat(info.format)
    };

    if (vkCreateImage(device->outputDevice->device, &imageInfo, NULL, &texture->texture->image) != VK_SUCCESS)
        return GN_FAILED_TO_CREATE_IMAGE;

    return GN_SUCCESS;
}
