#include "opengl_loader.h"
#include "device/opengl_output_device.h"
#include "presentation_queue/opengl_presentation_queue.h"

gnDeviceFunctions loadOpenGLDeviceFunctions() {
    return (gnDeviceFunctions){
        ._gnCreatePresentationQueue = createOpenGLPresentationQueue,
        ._gnPresentationQueueGetImage = getOpenGLPresentationQueueImage,
        ._gnDestroyPresentationQueue = destroyOpenGLPresentationQueue,

        ._gnCreateShaderModule = NULL,
        ._gnDestroyShaderModule = NULL,

        ._gnCreateRenderPassDescriptor = NULL,
        ._gnDestroyRenderPassDescriptor = NULL,

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

        ._gnCreateUniformPool = NULL,
        ._gnUniformPoolAllocateUniforms = NULL,
        ._gnDestroyUniformPool = NULL,

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
