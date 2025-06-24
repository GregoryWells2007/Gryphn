#pragma once
#include "stdint.h"
#include "stdlib.h"
#include "utils/gryphn_error_code.h"
#include "gryphn_handles.h"

typedef struct gnPresentationQueueInfo gnPresentationQueueInfo;
typedef struct gnShaderModuleInfo gnShaderModuleInfo;
typedef struct gnRenderPassDescriptorInfo gnRenderPassDescriptorInfo;
typedef struct gnGraphicsPipelineInfo gnGraphicsPipelineInfo;
typedef struct gnFramebufferInfo gnFramebufferInfo;
typedef struct gnCommandPoolInfo gnCommandPoolInfo;
typedef struct gnBufferInfo gnBufferInfo;
typedef struct gnUniformAllocationInfo gnUniformAllocationInfo;
typedef struct gnBufferUniformInfo gnBufferUniformInfo;
typedef struct gnImageUniformInfo gnImageUniformInfo;
typedef struct gnTextureInfo gnTextureInfo;
typedef struct gnSubmitInfo gnSubmitInfo;
typedef struct gnPresentInfo gnPresentInfo;

typedef struct gnDeviceFunctions {
    gnReturnCode (*_gnCreatePresentationQueue)(gnPresentationQueueHandle presentationQueue, const gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo);
    gnReturnCode (*_gnPresentationQueueGetImage)(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex);
    void (*_gnDestroyPresentationQueue)(gnPresentationQueueHandle presentationQueue);

    gnReturnCode (*_gnCreateShaderModule)(gnShaderModuleHandle module, gnOutputDeviceHandle device, gnShaderModuleInfo shaderModuleInfo);
    void (*_gnDestroyShaderModule)(gnShaderModuleHandle module);

    gnReturnCode (*_gnCreateRenderPassDescriptor)(gnRenderPassDescriptorHandle renderPass, gnOutputDeviceHandle device, gnRenderPassDescriptorInfo info);
    void (*_gnDestroyRenderPassDescriptor)(gnRenderPassDescriptorHandle renderPass);

    gnReturnCode (*_gnCreateGraphicsPipeline)(gnGraphicsPipelineHandle pipeline, gnOutputDeviceHandle device, gnGraphicsPipelineInfo pipelineInfo);
    void (*_gnDestroyGraphicsPipeline)(gnGraphicsPipelineHandle pipeline);

    gnReturnCode (*_gnCreateFramebuffer)(gnFramebuffer framebuffer, gnOutputDeviceHandle device, gnFramebufferInfo framebufferInfo);
    void (*_gnDestroyFramebuffer)(gnFramebuffer framebuffer);

    gnReturnCode (*_gnCreateCommandPool)(gnCommandPoolHandle commandPool, gnOutputDeviceHandle device, gnCommandPoolInfo info);
    void (*_gnDestroyCommandPool)(gnCommandPoolHandle commandPool);

    gnReturnCode (*_gnCreateSemaphore)(gnSemaphoreHandle semaphore, gnOutputDeviceHandle device);
    void (*_gnDestroySemaphore)(gnSemaphoreHandle semaphore);

    gnReturnCode (*_gnCreateBuffer)(gnBufferHandle buffer, gnDeviceHandle device, gnBufferInfo info);
    void (*_gnBufferData)(gnBufferHandle buffer, size_t size, void* data);
    void* (*_gnMapBuffer)(gnBufferHandle buffer);
    void (*_gnDestroyBuffer)(gnBufferHandle buffer);

    gnReturnCode (*_gnCreateUniformPool)(gnUniformPool pool, gnDeviceHandle device);
    gnUniform* (*_gnUniformPoolAllocateUniforms)(gnUniformPool pool, gnUniformAllocationInfo allocInfo);
    void (*_gnDestroyUniformPool)(gnUniformPool pool);

    void (*_gnUpdateBufferUniform)(gnUniform uniform, gnBufferUniformInfo* bufferInfo);
    void (*_gnUpdateImageUniform)(gnUniform uniform, gnImageUniformInfo* imageInfo);

    gnReturnCode (*_gnCreateTexture)(gnTexture texture, gnDevice device, const gnTextureInfo info);
    void (*_gnTextureData)(gnTextureHandle texture, void* pixelData);
    void (*_gnDestroyTexture)(gnTexture texture);

    gnReturnCode (*_gnCreateFence)(gnFenceHandle fence, gnOutputDeviceHandle device);
    void (*_gnSignalFence)(gnFenceHandle fence);
    void (*_gnWaitForFence)(gnFenceHandle fence, uint64_t timeout);
    void (*_gnResetFence)(gnFenceHandle fence);
    void (*_gnDestroyFence)(gnFenceHandle fence);

    gnReturnCode (*_gnSubmit)(gnOutputDeviceHandle device, gnSubmitInfo submit);
    gnReturnCode (*_gnPresent)(gnOutputDeviceHandle device, gnPresentInfo info);

    void (*_gnWaitForDevice)(gnOutputDeviceHandle device);
} gnDeviceFunctions;
