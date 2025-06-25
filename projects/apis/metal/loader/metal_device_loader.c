#include "metal_loader.h"

gnDeviceFunctions loadMetalDeviceFunctions() {
    return (gnDeviceFunctions){
        ._gnCreatePresentationQueue = NULL,
        ._gnPresentationQueueGetImage = NULL,
        ._gnDestroyPresentationQueue = NULL,

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

        ._gnCreateSemaphore = NULL,
        ._gnDestroySemaphore = NULL,

        ._gnCreateBuffer = NULL,
        ._gnBufferData = NULL,
        ._gnMapBuffer = NULL,
        ._gnDestroyBuffer = NULL,

        ._gnCreateUniformPool = NULL,
        ._gnUniformPoolAllocateUniforms = NULL,
        ._gnDestroyUniformPool = NULL,

        ._gnUpdateBufferUniform = NULL,
        ._gnUpdateImageUniform = NULL,

        ._gnCreateTexture = NULL,
        ._gnTextureData = NULL,
        ._gnDestroyTexture = NULL,

        ._gnCreateFence = NULL,
        ._gnWaitForFence = NULL,
        ._gnResetFence = NULL,
        ._gnDestroyFence = NULL,

        ._gnSubmit = NULL,
        ._gnPresent = NULL,

        ._gnWaitForDevice = NULL
    };
}
