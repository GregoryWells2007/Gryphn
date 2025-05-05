#include "core/graphics_pipeline/gryphn_render_pass_frame.h"
#include "../framebuffers/vulkan_framebuffer.h"
#include "vulkan_renderpass.h"

// void vkRenderPassFrame(gnRenderPassFrame* renderPassFrame) {
//     if (renderPassFrame->renderPassFrame == nullptr) renderPassFrame->renderPassFrame = new gnPlatformRenderPassFrame();
//     renderPassFrame->renderPassFrame->renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
// }

// std::array<VkClearValue, 2> clearValues{};

// void gnRenderPassFrameSetClearColor(gnRenderPassFrame& frame, gnColor clearColor) {
//     clearValues[0].color = {{clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a}};
//     clearValues[1].depthStencil = {1.0f, 0};

//     frame.renderPassFrame->renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
//     frame.renderPassFrame->renderPassInfo.pClearValues = clearValues.data();
// }
