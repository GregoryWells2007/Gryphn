#include "vulkan_framebuffer.h"
#include "textures/vulkan_texture.h"
#include "renderpass/vulkan_render_pass_descriptor.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode createFramebuffer(gnFramebuffer framebuffer, gnDevice device, gnFramebufferInfo info) {
    framebuffer->framebuffer = malloc(sizeof(struct gnPlatformFramebuffer_t));

    VkImageView* attachments = malloc(sizeof(VkImageView) * info.attachmentCount);
    for (int i = 0; i < info.attachmentCount; i++)
        attachments[i] = info.attachments[i]->texture->image.imageView;

    VkFramebufferCreateInfo framebufferInfo = {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .renderPass = info.renderPassDescriptor->renderPassDescriptor->renderPass,
        .attachmentCount = info.attachmentCount,
        .pAttachments = attachments,
        .width = info.size.x,
        .height = info.size.y,
        .layers = 1
    };

    if (vkCreateFramebuffer(device->outputDevice->device, &framebufferInfo, NULL, &framebuffer->framebuffer->framebuffer) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_FRAMEBUFFER;
    }

    free(attachments);
    return GN_SUCCESS;
}

void destroyFramebuffer(gnFramebuffer framebuffer) {
    vkDestroyFramebuffer(framebuffer->device->outputDevice->device, framebuffer->framebuffer->framebuffer, NULL);
    free(framebuffer->framebuffer);
}
