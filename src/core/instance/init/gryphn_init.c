// #undef GN_UTILS_CPP
#include "gryphn_init.h"
#include <platform/gryphn_platform_include.h>
#include "gryphn_dynamic_library.h"
// #include <dlfcn.h>
#include "stdbool.h"
#include "stdio.h"

gnBool gnIsAPISupported(gnRenderingAPI api) {
    int renderingAPICount = 0;
    gnRenderingAPI* supportedRenderingAPIS = gnGetSupportedRenderingAPIs(&renderingAPICount);
    for (int i = 0; i < renderingAPICount; i++) if (supportedRenderingAPIS[i] == api) return true;
    return false;
}

struct gnDynamicLibrary_t* gnLoadRenderingDLL(gnRenderingAPI renderingAPI) {
    gnString libName = gnCreateEmptyString();

    switch (renderingAPI) {
        case GN_RENDERINGAPI_NONE: return NULL;
        case GN_RENDERINGAPI_SOFTWARE: return NULL;
        case GN_RENDERINGAPI_OPENGL: return NULL;
        case GN_RENDERINGAPI_VULKAN: {
            if (!gnIsAPISupported(GN_RENDERINGAPI_VULKAN)) return NULL;
            libName = gnCreateString("GryphnVulkanImpl");
            break;
        }
        case GN_RENDERINGAPI_DIRECTX11: return NULL;
        case GN_RENDERINGAPI_DIRECTX12: return NULL;
        case GN_RENDERINGAPI_METAL: {
            if (!gnIsAPISupported(GN_RENDERINGAPI_METAL)) return NULL;
            libName = gnCreateString("GryphnMetalImpl");
            break;
        }
    }

    return gnLoadDynamicLibrary(gnCombineStrings(gnCreateString("gryphn/rendering_apis/"), libName));
}

void gnLoadFunctions(struct gnDynamicLibrary_t* lib, struct gnFunctions_t* functions) {
    gnLoadDLLFunction(lib, functions->_gnCreateInstance, "gnCreateInstanceFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyInstance, "gnDestroyInstanceFn");
    gnLoadDLLFunction(lib, functions->_gnCreateDebugger, "gnCreateDebuggerFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyDebugger, "gnDestroyDebuggerFn");
    gnLoadDLLFunction(lib, functions->_gnGetPhysicalDevices, "gnGetPhysicalDevicesFn");
    gnLoadDLLFunction(lib, functions->_gnQueueCanPresentToSurface, "gnQueueCanPresentToSurfaceFn");
    gnLoadDLLFunction(lib, functions->_gnCreateOutputDevoce, "gnCreateOutputDeviceFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyOutputDevice, "gnDestroyOutputDeviceFn");

    #ifdef GN_PLATFORM_LINUX
        #ifdef GN_WINDOW_X11
        gnLoadDLLFunction(lib, functions->_gnCreateX11WindowSurface, "gnCreateX11WindowSurfaceFn");
        #endif
        #ifdef GN_WINDOW_WAYLAND
        gnLoadDLLFunction(lib, functions->_gnCreateWaylandWindowSurface, "gnCreateWaylandWindowSurfaceFn");
        #endif
    #endif


    #ifdef GN_PLATFORM_WIN32
    gnLoadDLLFunction(lib, functions->_gnCreateWin32WindowSurface, "gnCreateWin32WindowSurfaceFn");
    #endif

    #ifdef GN_PLATFORM_MACOS
    gnLoadDLLFunction(lib, functions->_gnCreateMacOSWindowSurface, "gnCreateMacOSWindowSurfaceFn");
    #endif

    gnLoadDLLFunction(lib, functions->_gnDestroyWindowSurface, "gnDestroyWindowSurfaceFn");
    gnLoadDLLFunction(lib, functions->_gnGetSurfaceDetails, "gnGetSurfaceDetailsFn");
}

void gnLoadDeviceFunctions(struct gnDynamicLibrary_t* lib, struct gnDeviceFunctions_t* functions) {
    gnLoadDLLFunction(lib, functions->_gnCreatePresentationQueue, "gnCreatePresentationQueueFn");
    gnLoadDLLFunction(lib, functions->_gnPresentationQueueGetImage, "gnPresentationQueueGetImageFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyPresentationQueue, "gnDestroyPresentationQueueFn");
    gnLoadDLLFunction(lib, functions->_gnCreateShaderModule, "gnCreateShaderModuleFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyShaderModule, "gnDestroyShaderModuleFn");
    gnLoadDLLFunction(lib, functions->_gnCreateRenderPassDescriptor, "gnCreateRenderPassDescriptorFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyRenderPassDescriptor, "gnDestroyRenderPassDescriptorFn");
    gnLoadDLLFunction(lib, functions->_gnCreateGraphicsPipeline, "gnCreateGraphicsPipelineFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyGraphicsPipeline, "gnDestroyGraphicsPipelineFn");
    gnLoadDLLFunction(lib, functions->_gnCreateFramebuffer, "gnCreateFramebufferFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyFramebuffer, "gnDestroyFramebufferFn");
    gnLoadDLLFunction(lib, functions->_gnCreateCommandPool, "gnCreateCommandPoolFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyCommandPool, "gnDestroyCommandPoolFn");
    gnLoadDLLFunction(lib, functions->_gnCreateSemaphore, "gnCreateSemaphoreFn");
    gnLoadDLLFunction(lib, functions->_gnDestroySemaphore, "gnDestroySemaphoreFn");
    gnLoadDLLFunction(lib, functions->_gnCreateBuffer, "gnCreateBufferFn");
    gnLoadDLLFunction(lib, functions->_gnBufferData, "gnBufferDataFn");
    gnLoadDLLFunction(lib, functions->_gnMapBuffer, "gnMapBufferFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyBuffer, "gnDestroyBufferFn");
    gnLoadDLLFunction(lib, functions->_gnCreateUniformPool, "gnCreateUniformPoolFn");
    gnLoadDLLFunction(lib, functions->_gnUniformPoolAllocateUniforms, "gnUniformPoolAllocateUniformsFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyUniformPool, "gnDestroyUniformPoolFn");
    gnLoadDLLFunction(lib, functions->_gnUpdateBufferUniform, "gnUpdateBufferUniformFn");
    gnLoadDLLFunction(lib, functions->_gnCreateTexture, "gnCreateTextureFn");
    gnLoadDLLFunction(lib, functions->_gnCreateFence, "gnCreateFenceFn");
    gnLoadDLLFunction(lib, functions->_gnSignalFence, "gnSignalFenceFn");
    gnLoadDLLFunction(lib, functions->_gnWaitForFence, "gnWaitForFenceFn");
    gnLoadDLLFunction(lib, functions->_gnResetFence, "gnResetFenceFn");
    gnLoadDLLFunction(lib, functions->_gnDestroyFence, "gnDestroyFenceFn");
    gnLoadDLLFunction(lib, functions->_gnSubmit, "gnSubmitFn");
    gnLoadDLLFunction(lib, functions->_gnPresent, "gnPresentFn");
    gnLoadDLLFunction(lib, functions->_gnWaitForDevice, "gnWaitForDeviceFn");
}

void gnLoadCommandFunctions(struct gnDynamicLibrary_t* lib, struct gnCommandFunctions_t* functions) {
    gnLoadDLLFunction(lib, functions->_gnCommandPoolAllocateCommandBuffers, "gnCommandPoolAllocateCommandBuffersFn");
    gnLoadDLLFunction(lib, functions->_gnBeginCommandBuffer, "gnBeginCommandBufferFn");
    gnLoadDLLFunction(lib, functions->_gnResetCommandBuffer, "gnResetCommandBufferFn");
    gnLoadDLLFunction(lib, functions->_gnEndCommandBuffer, "gnEndCommandBufferFn");
    gnLoadDLLFunction(lib, functions->_gnCommandBeginRenderPass, "gnCommandBeginRenderPassFn");
    gnLoadDLLFunction(lib, functions->_gnCommandEndRenderPass, "gnCommandEndRenderPassFn");
    gnLoadDLLFunction(lib, functions->_gnCommandBindGraphicsPipeline, "gnCommandBindGraphicsPipelineFn");
    gnLoadDLLFunction(lib, functions->_gnCommandSetViewport, "gnCommandSetViewportFn");
    gnLoadDLLFunction(lib, functions->_gnCommandSetScissor, "gnCommandSetScissorFn");
    gnLoadDLLFunction(lib, functions->_gnCommandBindUniform, "gnCommandBindUniformFn");
    gnLoadDLLFunction(lib, functions->_gnCommandBindBuffer, "gnCommandBindBufferFn");
    gnLoadDLLFunction(lib, functions->_gnCommandDraw, "gnCommandDrawFn");
    gnLoadDLLFunction(lib, functions->_gnCommandDrawIndexed, "gnCommandDrawIndexedFn");
}
