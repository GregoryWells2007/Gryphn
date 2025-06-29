#include "metal_loader.h"
#include "presentation_queue/metal_presentation_queue.h"
#include "shader_module/metal_shader_module.h"
#include "renderpass/metal_render_pass.h"
#include "framebuffers/metal_framebuffer.h"
#include "uniforms/metal_uniform_pool.h"
#include "pipelines/graphics_pipeline/metal_graphics_pipeline.h"
#include "texture/metal_texture.h"
#include "commands/command_pool/metal_command_pool.h"
#include "buffer/metal_buffer.h"
#include "uniforms/metal_uniform.h"
#include "sync/semaphore/metal_semaphore.h"
#include "sync/fence/metal_fence.h"
#include "submit/metal_submit.h"
#include "present/metal_present.h"

gnDeviceFunctions loadMetalDeviceFunctions() {
    return (gnDeviceFunctions){
        ._gnCreatePresentationQueue = createMetalPresentationQueue,
        ._gnPresentationQueueGetImage = getMetalPresentQueueImage,
        ._gnDestroyPresentationQueue = destroyMetalPresentationQueue,

        ._gnCreateShaderModule = createMetalShaderModule,
        ._gnDestroyShaderModule = destroyMetalShaderModule,

        ._gnCreateRenderPassDescriptor = createMetalRenderPass,
        ._gnDestroyRenderPassDescriptor = destroyMetalRenderPass,

        ._gnCreateGraphicsPipeline = createMetalGraphicsPipeline,
        ._gnDestroyGraphicsPipeline = destroyMetalGraphicsPipeline,

        ._gnCreateFramebuffer = createMetalFramebuffer,
        ._gnDestroyFramebuffer = destroyMetalFramebuffer,

        ._gnCreateCommandPool = createMetalCommandPool,
        ._gnDestroyCommandPool = destroyMetalCommandPool,

        ._gnCreateSemaphore = createMetalSemaphore,
        ._gnDestroySemaphore = destroyMetalSemaphore,

        ._gnCreateBuffer = createMetalBuffer,
        ._gnBufferData = metalBufferData,
        ._gnMapBuffer = mapMetalBuffer,
        ._gnDestroyBuffer = destroyMetalBuffer,

        ._gnCreateUniformPool = createMetalUniformPool,
        ._gnUniformPoolAllocateUniforms = allocateMetalUniforms,
        ._gnDestroyUniformPool = destroyMetalUniformPool,

        ._gnUpdateBufferUniform = updateMetalBufferUniform,
        ._gnUpdateImageUniform = updateMetalImageUniform,

        ._gnCreateTexture = createMetalTexture,
        ._gnTextureData = metalTextureData,
        ._gnDestroyTexture = metalDestroyTexture,

        ._gnCreateFence = createMetalFence,
        ._gnWaitForFence = waitForMetalFence,
        ._gnResetFence = resetMetalFence,
        ._gnDestroyFence = destroyMetalFence,

        ._gnSubmit = metalSubmit,
        ._gnPresent = metalPresent,

        ._gnWaitForDevice = waitForMetalDevice
    };
}
