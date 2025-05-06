#include <core/graphics_pipeline/gryphn_render_pass.h>
#include <Metal/Metal.hpp>

// okay so my understanding is that there is no such thing as a MTL::Subpass or any alternative
// so instread every render pass is instread going to be an array of render passes and
// im going to find a way to implment error handling if the user attempts to to try and access different
// resources or something like that
struct gnPlatformRenderPass {
    // MTL::RenderPassDescriptor* renderPassDescriptor = nullptr;
};
struct gnPlatformSubpass {};
struct gnPlatformRenderpassAttachment {};

// all this function is resposible for is making sure that youre whole render pass will be valid when
// created at runtime, I fucking hate you metal more than vulkan, I wish everything was explicit like
// vulkan, can I just define everything at compile time please
GN_EXPORT gnReturnCode gnCreateRenderPassFn(gnRenderPass* renderPass, const gnOutputDevice& outputDevice) {
    // renderPass->renderpass = new gnPlatformRenderPass();
    // renderPass->renderpass->renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();

    for (int i = 0; i < renderPass->attachmentCount; i++) {
        renderPass->attachments[i].renderpassAttachment = new gnPlatformRenderpassAttachment();
        if (renderPass->attachments[i].colorMode == GN_RGBA8) {}
        else if (renderPass->attachments[i].colorMode == GN_DEPTH8_STENCIL24) {}
        else {
            std::string return_code = "GN_RENDERPASS_ATTATCHMENT_(" + std::to_string(i) + ")" + "_UNSUPPORTED_COLOR_MODE";
            return gnReturnError(GN_UNKNOWN_COLOR_FORMAT, return_code.c_str());
        }
    }

    return GN_SUCCESS;
}
GN_EXPORT void gnDestroyRenderPassFn(gnRenderPass& renderPass) {
    //renderPass.renderpass->renderPassDescriptor->release();
    return;
}
