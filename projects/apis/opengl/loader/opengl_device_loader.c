#include "opengl_loader.h"
#include "device/opengl_output_device.h"
#include "presentation_queue/opengl_presentation_queue.h"
#include "shaders/opengl_shader_module.h"
#include "renderpass/opengl_render_pass_descriptor.h"
#include "uniforms/pool/opengl_uniform_pool.h"

gnDeviceFunctions loadOpenGLDeviceFunctions() {
    return (gnDeviceFunctions){
        ._gnCreatePresentationQueue = createOpenGLPresentationQueue,
        ._gnPresentationQueueGetImage = getOpenGLPresentationQueueImage,
        ._gnDestroyPresentationQueue = destroyOpenGLPresentationQueue,

        ._gnCreateShaderModule = openglCreateShaderModule,
        ._gnDestroyShaderModule = openglDestroyShaderModule,

        ._gnCreateRenderPassDescriptor = openglCreateRenderPass,
        ._gnDestroyRenderPassDescriptor = openglDestroyRenderPass,

        ._gnCreateGraphicsPipeline = NULL,
        ._gnDestroyGraphicsPipeline = NULL,

        ._gnCreateFramebuffer = NULL,
        ._gnDestroyFramebuffer = NULL,

        ._gnCreateCommandPool = NULL,
        ._gnDestroyCommandPool = NULL,

        ._gnCreateBuffer = NULL,
        ._gnBufferData = NULL,
        ._gnBufferSubData = NULL,
        ._gnMapBuffer = NULL,
        ._gnDestroyBuffer = NULL,

        ._gnCreateUniformPool = openglCreateUniformPool,
        ._gnUniformPoolAllocateUniforms = openglAllocateUniforms,
        ._gnDestroyUniformPool = openglDestroyUniformPool,

        ._gnUpdateBufferUniform = NULL,
        ._gnUpdateStorageUniform = NULL,
        ._gnUpdateImageUniform = NULL,

        ._gnCreateTexture = NULL,
        ._gnTextureData = NULL,
        ._gnDestroyTexture = NULL,

        ._gnSubmit = NULL,
        ._gnPresent = NULL,

        ._gnWaitForDevice = waitForOpenGLDevice
    };
}
