#include "opengl_loader.h"
#include "device/opengl_output_device.h"
#include "presentation_queue/opengl_presentation_queue.h"
#include "shaders/opengl_shader_module.h"
#include "renderpass/opengl_render_pass_descriptor.h"
#include "uniforms/pool/opengl_uniform_pool.h"
#include "uniforms/uniform/opengl_uniform.h"
#include "commands/pool/opengl_command_pool.h"
#include "buffer/opengl_buffer.h"
#include "textures/opengl_texture.h"

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

        ._gnCreateCommandPool = openglCreateCommandPool,
        ._gnDestroyCommandPool = openglDestroyCommandPool,

        ._gnCreateBuffer = openglCreateBuffer,
        ._gnBufferData = openglBufferData,
        ._gnBufferSubData = openglBufferSubData,
        ._gnMapBuffer = openglMapBuffer,
        ._gnUnmapBuffer = openglUnmapBuffer,
        ._gnDestroyBuffer = openglDestroyBuffer,

        ._gnCreateUniformPool = openglCreateUniformPool,
        ._gnUniformPoolAllocateUniforms = openglAllocateUniforms,
        ._gnDestroyUniformPool = openglDestroyUniformPool,

        ._gnUpdateBufferUniform = openglUpdateBufferUniform,
        ._gnUpdateStorageUniform = openglUpdateStorageUniform,
        ._gnUpdateImageUniform = openglUpdateImageUniform,

        ._gnCreateTexture = openglCreateTexture,
        ._gnTextureData = openglTextureData,
        ._gnDestroyTexture = openglDestroyTexture,

        ._gnSubmit = NULL,
        ._gnPresent = NULL,

        ._gnWaitForDevice = waitForOpenGLDevice
    };
}
