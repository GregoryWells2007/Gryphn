#include "vulkan_loader.h"
#include <presentation_queue/vulkan_presentation_queue.h>

gnDeviceFunctions loadVulkanDeviceFunctions() {
    return (gnDeviceFunctions){
        ._gnCreatePresentationQueue = createPresentationQueue,
        ._gnPresentationQueueGetImage = getPresentQueueImage,
        ._gnDestroyPresentationQueue = destroyPresentationQueue

        // gnReturnCode (*_gnCreateShaderModule)(gnShaderModuleHandle module, gnOutputDeviceHandle device, gnShaderModuleInfo shaderModuleInfo);
        // void (*_gnDestroyShaderModule)(gnShaderModuleHandle module);

        // gnReturnCode (*_gnCreateRenderPassDescriptor)(gnRenderPassDescriptorHandle renderPass, gnOutputDeviceHandle device, gnRenderPassDescriptorInfo info);
        // void (*_gnDestroyRenderPassDescriptor)(gnRenderPassDescriptorHandle renderPass);

        // gnReturnCode (*_gnCreateGraphicsPipeline)(gnGraphicsPipelineHandle pipeline, gnOutputDeviceHandle device, gnGraphicsPipelineInfo pipelineInfo);
        // void (*_gnDestroyGraphicsPipeline)(gnGraphicsPipelineHandle pipeline);

        // gnReturnCode (*_gnCreateFramebuffer)(gnFramebuffer framebuffer, gnOutputDeviceHandle device, gnFramebufferInfo framebufferInfo);
        // void (*_gnDestroyFramebuffer)(gnFramebuffer framebuffer);

        // gnReturnCode (*_gnCreateCommandPool)(gnCommandPoolHandle commandPool, gnOutputDeviceHandle device, gnCommandPoolInfo info);
        // void (*_gnDestroyCommandPool)(gnCommandPoolHandle commandPool);

        // gnReturnCode (*_gnCreateSemaphore)(gnSemaphoreHandle semaphore, gnOutputDeviceHandle device);
        // void (*_gnDestroySemaphore)(gnSemaphoreHandle semaphore);

        // gnReturnCode (*_gnCreateBuffer)(gnBufferHandle buffer, gnDeviceHandle device, gnBufferInfo info);
        // void (*_gnBufferData)(gnBufferHandle buffer, size_t size, void* data);
        // void* (*_gnMapBuffer)(gnBufferHandle buffer);
        // void (*_gnDestroyBuffer)(gnBufferHandle buffer);

        // gnReturnCode (*_gnCreateUniformPool)(gnUniformPool pool, gnDeviceHandle device);
        // gnUniform* (*_gnUniformPoolAllocateUniforms)(gnUniformPool pool, gnUniformAllocationInfo allocInfo);
        // void (*_gnDestroyUniformPool)(gnUniformPool pool);

        // void (*_gnUpdateBufferUniform)(gnUniform uniform, gnBufferUniformInfo* bufferInfo);
        // void (*_gnUpdateImageUniform)(gnUniform uniform, gnImageUniformInfo* imageInfo);

        // gnReturnCode (*_gnCreateTexture)(gnTexture texture, gnDevice device, const gnTextureInfo info);
        // void (*_gnTextureData)(gnTextureHandle texture, void* pixelData);
        // void (*_gnDestroyTexture)(gnTexture texture);

        // gnReturnCode (*_gnCreateFence)(gnFenceHandle fence, gnOutputDeviceHandle device);
        // void (*_gnSignalFence)(gnFenceHandle fence);
        // void (*_gnWaitForFence)(gnFenceHandle fence, uint64_t timeout);
        // void (*_gnResetFence)(gnFenceHandle fence);
        // void (*_gnDestroyFence)(gnFenceHandle fence);

        // gnReturnCode (*_gnSubmit)(gnOutputDeviceHandle device, gnSubmitInfo submit);
        // gnReturnCode (*_gnPresent)(gnOutputDeviceHandle device, gnPresentInfo info);

        // void (*_gnWaitForDevice)(gnOutputDeviceHandle device);
    };
}
