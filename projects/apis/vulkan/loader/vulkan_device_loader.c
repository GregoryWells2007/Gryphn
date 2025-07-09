#include "vulkan_loader.h"
#include <presentation_queue/vulkan_presentation_queue.h>
#include <shader_module/vulkan_shader_module.h>
#include <renderpass/vulkan_render_pass_descriptor.h>
#include <pipelines/graphics_pipeline/vulkan_graphics_pipeline.h>
#include <framebuffers/vulkan_framebuffer.h>
#include <textures/vulkan_texture.h>
#include <uniforms/vulkan_uniform_pool.h>
#include <uniforms/vulkan_uniform.h>
#include <commands/command_pool/vulkan_command_pool.h>
#include <buffers/vulkan_buffer.h>
#include <sync/semaphore/vulkan_semaphore.h>
#include <sync/fence/vulkan_fence.h>
#include <present/vulkan_present.h>
#include <submit/vulkan_submit.h>
#include <output_device/vulkan_output_devices.h>

gnDeviceFunctions loadVulkanDeviceFunctions() {
    return (gnDeviceFunctions){
        ._gnCreatePresentationQueue = createPresentationQueue,
        // ._gnPresentationQueueGetImageAsync = getPresentQueueImageAsync,
        ._gnDestroyPresentationQueue = destroyPresentationQueue,

        ._gnCreateShaderModule = createShaderModule,
        ._gnDestroyShaderModule = destroyShaderModule,

        ._gnCreateRenderPassDescriptor = createRenderPass,
        ._gnDestroyRenderPassDescriptor = destroyRenderPass,

        ._gnCreateGraphicsPipeline = createGraphicsPipeline,
        ._gnDestroyGraphicsPipeline = destroyGraphicsPipeline,

        ._gnCreateFramebuffer = createFramebuffer,
        ._gnDestroyFramebuffer = destroyFramebuffer,

        ._gnCreateCommandPool = createCommandPool,
        ._gnDestroyCommandPool = destroyCommandPool,

        // ._gnCreateSemaphore = createSemaphore,
        // ._gnDestroySemaphore = destroySemaphore,

        ._gnCreateBuffer = createBuffer,
        ._gnBufferData = bufferData,
        ._gnBufferSubData = vulkanBufferSubData,
        ._gnMapBuffer = mapBuffer,
        ._gnDestroyBuffer = destroyBuffer,

        ._gnCreateUniformPool = createUniformPool,
        ._gnUniformPoolAllocateUniforms = allocateUniforms,
        ._gnDestroyUniformPool = destroyUniformPool,

        ._gnUpdateBufferUniform = updateBufferUniform,
        ._gnUpdateStorageUniform = updateVulkanStorageUniform,
        ._gnUpdateImageUniform = updateImageUniform,

        ._gnCreateTexture = createTexture,
        ._gnTextureData = textureData,
        ._gnDestroyTexture = destroyTexture,

        // ._gnCreateFence = createFence,
        // ._gnWaitForFence = waitForFence,
        // ._gnResetFence = resetFence,
        // ._gnDestroyFence = destroyFence,

        ._gnSubmit = submit,
        ._gnPresent = present,

        ._gnWaitForDevice = waitForDevice
    };
}
