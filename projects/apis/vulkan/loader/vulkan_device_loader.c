#include "vulkan_loader.h"
#include <presentation_queue/vulkan_presentation_queue.h>
#include <shader_module/vulkan_shader_module.h>
#include <renderpass/vulkan_render_pass_descriptor.h>
#include <pipelines/graphics_pipeline/vulkan_graphics_pipeline.h>
#include <framebuffers/vulkan_framebuffer.h>
#include <textures/vulkan_texture.h>
#include <uniforms/vulkan_uniform_pool.h>
#include <commands/command_pool/vulkan_command_pool.h>
#include <output_device/vulkan_output_devices.h>

gnDeviceFunctions loadVulkanDeviceFunctions() {
    return (gnDeviceFunctions){
        ._gnCreatePresentationQueue = createPresentationQueue,
        ._gnPresentationQueueGetImage = getPresentQueueImage,
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

        // gnReturnCode (*_gnCreateSemaphore)(gnSemaphoreHandle semaphore, gnOutputDeviceHandle device);
        // void (*_gnDestroySemaphore)(gnSemaphoreHandle semaphore);

        // gnReturnCode (*_gnCreateBuffer)(gnBufferHandle buffer, gnDeviceHandle device, gnBufferInfo info);
        // void (*_gnBufferData)(gnBufferHandle buffer, size_t size, void* data);
        // void* (*_gnMapBuffer)(gnBufferHandle buffer);
        // void (*_gnDestroyBuffer)(gnBufferHandle buffer);

        ._gnCreateUniformPool = createUniformPool,
        ._gnUniformPoolAllocateUniforms = allocateUniforms,
        ._gnDestroyUniformPool = destroyUniformPool,

        // void (*_gnUpdateBufferUniform)(gnUniform uniform, gnBufferUniformInfo* bufferInfo);
        // void (*_gnUpdateImageUniform)(gnUniform uniform, gnImageUniformInfo* imageInfo);

        ._gnCreateTexture = createTexture,
        ._gnTextureData = textureData,
        ._gnDestroyTexture = destroyTexture,

        // gnReturnCode (*_gnCreateFence)(gnFenceHandle fence, gnOutputDeviceHandle device);
        // void (*_gnSignalFence)(gnFenceHandle fence);
        // void (*_gnWaitForFence)(gnFenceHandle fence, uint64_t timeout);
        // void (*_gnResetFence)(gnFenceHandle fence);
        // void (*_gnDestroyFence)(gnFenceHandle fence);

        // gnReturnCode (*_gnSubmit)(gnOutputDeviceHandle device, gnSubmitInfo submit);
        // gnReturnCode (*_gnPresent)(gnOutputDeviceHandle device, gnPresentInfo info);

        ._gnWaitForDevice = waitForDevice
    };
}
