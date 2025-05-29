#include "vulkan_framebuffer.h"
#include "textures/vulkan_texture.h"
#include "renderpass/vulkan_render_pass_descriptor.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode gnCreateFramebufferFn(struct gnFramebuffer_t* framebuffer, struct gnOutputDevice_t* device, struct gnFramebufferInfo_t info) {
    framebuffer->framebuffer = malloc(sizeof(struct gnPlatformFramebuffer_t));

    VkImageView* attachments = malloc(sizeof(VkImageView) * info.attachmentCount);
    for (int i = 0; i < info.attachmentCount; i++)
        attachments[i] = info.attachments[i].texture->imageView;

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

void gnDestroyFramebufferFn(struct gnFramebuffer_t* framebuffer) {
    vkDestroyFramebuffer(framebuffer->device->outputDevice->device, framebuffer->framebuffer->framebuffer, NULL);
    free(framebuffer->framebuffer);
}
