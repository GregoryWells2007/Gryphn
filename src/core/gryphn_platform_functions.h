#pragma once
// theoretically you could have multible gryphn instances running in one application,
// why I dont know
#include "instance/gryphn_instance.h"
#include "debugger/gryphn_debugger.h"
#include "output_device/gryphn_physical_output_device.h"
#include "output_device/gryphn_output_device.h"
#include "window_surface/gryphn_surface.h"
#include "window_surface/gryphn_surface_create_functions.h"
#include "shader_module/gryphn_shader_module.h"
#include "renderpass/gryphn_render_pass_descriptor.h"
#include "pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "framebuffer/gryphn_framebuffer.h"
#include "command/command_pool/gryphn_command_pool.h"
#include "command/command_buffer/gryphn_command_buffer.h"
#include "renderpass/gryphn_render_pass.h"
#include "sync/fence/gryphn_fence.h"
#include "sync/semaphore/gryphn_semaphore.h"
#include "core/submit/gryphn_submit.h"
#include "core/present/gryphn_present.h"

typedef struct gnFunctions_t {
    gnReturnCode (*_gnCreateInstance)(gnInstanceHandle instance, struct gnInstanceInfo_t info);
    void (*_gnDestroyInstance)(gnInstanceHandle instance);

    gnReturnCode (*_gnCreateDebugger)(gnDebuggerHandle debugger, gnInstanceHandle instance, const struct gnDebuggerInfo_t info);
    void (*_gnDestroyDebugger)(gnDebuggerHandle debugger);

    gnPhysicalDevice* (*_gnGetPhysicalDevices)(gnInstanceHandle instance, uint32_t* count);
    gnBool (*_gnQueueCanPresentToSurface)(const struct gnPhysicalDevice_t device, uint32_t queueIndex, const gnWindowSurfaceHandle windowSurface);


    gnReturnCode (*_gnCreateOutputDevoce)(gnOutputDeviceHandle device, gnInstanceHandle instance, struct gnOutputDeviceInfo_t deviceInfo);
    void (*_gnDestroyOutputDevice)(gnOutputDeviceHandle device);



    #ifdef GN_PLATFORM_LINUX
        #ifdef GN_WINDOW_X11
            gnReturnCode (*_gnCreateX11WindowSurface)(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, struct gnX11WindowSurfaceInfo_t createInfo);
        #endif
        #ifdef GN_WINDOW_WAYLAND
            gnReturnCode (*_gnCreateWaylandWindowSurface)(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, struct gnWaylandWindowSurfaceInfo_t createInfo);
        #endif
    #endif


    #ifdef GN_PLATFORM_WIN32
        gnReturnCode (*_gnCreateWin32WindowSurface)(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, struct gnWin32WindowSurfaceInfo_t createInfo);
    #endif

    #ifdef GN_PLATFORM_MACOS
        gnReturnCode (*_gnCreateMacOSWindowSurface)(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, struct gnMacOSWindowSurfaceInfo_t createInfo);
    #endif

    void (*_gnDestroyWindowSurface)(gnWindowSurfaceHandle windowSurface);
    struct gnSurfaceDetails_t (*_gnGetSurfaceDetails)(gnWindowSurfaceHandle windowSurface, struct gnPhysicalDevice_t device);
} gnFunctions;

#include "core/presentation_queue/gryphn_presentation_queue.h"
typedef struct gnDeviceFunctions_t {
    gnReturnCode (*_gnCreatePresentationQueue)(gnPresentationQueueHandle presentationQueue, const gnOutputDeviceHandle device, struct gnPresentationQueueInfo_t presentationInfo);
    gnReturnCode (*_gnPresentationQueueGetImage)(gnPresentationQueueHandle presentationQueue, uint64_t timeout, struct gnSemaphore_t* semaphore, uint32_t* imageIndex);
    void (*_gnDestroyPresentationQueue)(gnPresentationQueueHandle presentationQueue);

    gnReturnCode (*_gnCreateShaderModule)(gnShaderModuleHandle module, gnOutputDeviceHandle device, struct gnShaderModuleInfo_t shaderModuleInfo);
    void (*_gnDestroyShaderModule)(gnShaderModuleHandle module);

    gnReturnCode (*_gnCreateRenderPassDescriptor)(gnRenderPassDescriptorHandle renderPass, gnOutputDeviceHandle device, struct gnRenderPassDescriptorInfo_t info);
    void (*_gnDestroyRenderPassDescriptor)(gnRenderPassDescriptorHandle renderPass);

    gnReturnCode (*_gnCreateGraphicsPipeline)(gnGraphicsPipelineHandle pipeline, gnOutputDeviceHandle device, struct gnGraphicsPipelineInfo_t pipelineInfo);
    void (*_gnDestroyGraphicsPipeline)(gnGraphicsPipelineHandle pipeline);

    gnReturnCode (*_gnCreateFramebuffer)(struct gnFramebuffer_t* framebuffer, gnOutputDeviceHandle device, struct gnFramebufferInfo_t framebufferInfo);
    void (*_gnDestroyFramebuffer)(struct gnFramebuffer_t* framebuffer);

    gnReturnCode (*_gnCreateCommandPool)(gnCommandPoolHandle commandPool, gnOutputDeviceHandle device, struct gnCommandPoolInfo_t info);
    void (*_gnDestroyCommandPool)(gnCommandPoolHandle commandPool);

    gnReturnCode (*_gnCreateSemaphore)(struct gnSemaphore_t* semaphore, gnOutputDeviceHandle device);
    void (*_gnDestroySemaphore)(struct gnSemaphore_t* semaphore);

    gnReturnCode (*_gnCreateFence)(struct gnFence_t* fence, gnOutputDeviceHandle device);
    void (*_gnSignalFence)(struct gnFence_t* fence);
    void (*_gnWaitForFence)(struct gnFence_t* fence, uint64_t timeout);
    void (*_gnResetFence)(struct gnFence_t* fence);
    void (*_gnDestroyFence)(struct gnFence_t* fence);

    gnReturnCode (*_gnSubmit)(gnOutputDeviceHandle device, gnSubmitInfo submit);
    gnReturnCode (*_gnPresent)(gnOutputDeviceHandle device, gnPresentInfo info);

    void (*_gnWaitForDevice)(gnOutputDeviceHandle device);
} gnDeviceFunctions;

typedef struct gnCommandFunctions_t {
    gnReturnCode (*_gnCommandPoolAllocateCommandBuffers)(gnCommandBufferHandle* commandBuffers, uint32_t count, gnCommandPoolHandle pool);
    gnReturnCode (*_gnBeginCommandBuffer)(gnCommandBufferHandle commandBuffer);
    void (*_gnResetCommandBuffer)(gnCommandBufferHandle commandBuffer);
    gnReturnCode (*_gnEndCommandBuffer)(gnCommandBufferHandle commandBuffer);

    void (*_gnCommandBeginRenderPass)(gnCommandBufferHandle buffer, struct gnRenderPassInfo_t passInfo);
    void (*_gnCommandEndRenderPass)(gnCommandBufferHandle buffer);

    void (*_gnCommandBindGraphicsPipeline)(gnCommandBufferHandle buffer, gnGraphicsPipelineHandle graphicsPipeline);
    void (*_gnCommandSetViewport)(gnCommandBufferHandle buffer, gnViewport viewport);
    void (*_gnCommandSetScissor)(gnCommandBufferHandle buffer, gnScissor scissor);

    void (*_gnCommandDraw)(gnCommandBufferHandle buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance);
} gnCommandFunctions;
