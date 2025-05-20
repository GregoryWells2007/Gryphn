// #undef GN_UTILS_CPP
#include "gryphn_init.h"
#include <platform/gryphn_platform_include.h>
#include "gryphn_dynamic_library.h"
// #include <dlfcn.h>

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
}

// gnReturnCode gnInit(gnRenderingAPI RenderingAPI) {

//     gnRenderingAPILIB = gnLoadDLL(gnCombineStrings(gnCreateString("gryphn/rendering_apis/"), libName));
//     if (!gnRenderingAPILIB.isValid) { return GN_UNABLE_TO_LOAD_DLL; }

//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateInstance, "gnCreateInstanceFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyInstance, "gnDestroyInstanceFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGetPlatformLayerName, "gnGetPlatformLayerNameFn");

//     // LOAD THE SET WINDOW FUNCTIONS
//     // #ifdef GN_PLATFORM_LINUX
//     //     #ifdef GN_WINDOW_X11
//     //         gnLoadDLLFunction(gnRenderingAPILIB, gnCreateX11WindowSurface, "gnCreateX11WindowSurfaceFn");
//     //     #endif
//     //     #ifdef GN_WINDOW_WAYLAND
//     //         gnLoadDLLFunction(gnRenderingAPILIB, gnCreateWaylandWindowSurface, "gnCreateWaylandWindowSurfaceFn");
//     //     #endif
//     // #endif


//     // #ifdef GN_PLATFORM_WIN32
//     //     gnLoadDLLFunction(gnRenderingAPILIB, gnCreateWindowsWindowSurface, "gnCreateWindowsWindowSurfaceFn");
//     // #endif

//     // #ifdef GN_PLATFORM_MACOS
//     //     gnLoadDLLFunction(gnRenderingAPILIB, gnCreateMacOSWindowSurface, "gnCreateMacOSWindowSurfaceFn");
//     // #endif
//     // This is stupid

//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateDebugger, "gnCreateDebuggerFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyDebugger, "gnDestroyDebuggerFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGetPhysicalOutputDevices, "gnGetPhysicalOutputDevicesFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDeviceSupportsAPI, "gnDeviceSupportsAPIFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnRegisterOutputDevice, "gnRegisterOutputDeviceFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnWaitForDevice, "gnWaitForDeviceFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyOutputDevice, "gnDestroyOutputDeviceFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGetDevicePresentationDetails, "gnGetDevicePresentationDetailsFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnPresentationQueueGetNextImageAsync, "gnPresentationQueueGetNextImageAsyncFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnPresentationQueueGetState, "gnPresentationQueueGetStateFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreatePresentationQueue, "gnCreatePresentationQueueFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyPresentationQueue, "gnDestroyPresentationQueueFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnVertexDescriptionSetBindingDescription, "gnVertexDescriptionSetBindingDescriptionFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnVertexDescriptionSetPropertiesCount, "gnVertexDescriptionSetPropertiesCountFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnVertexDescriptionSetProperty, "gnVertexDescriptionSetPropertyFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateBuffer, "gnCreateBufferFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnBufferData, "gnBufferDataFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnBufferMapData, "gnBufferMapDataFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyBuffer, "gnDestroyBufferFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnBufferSubData, "gnBufferSubDataFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnBufferClearData, "gnBufferClearDataFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnTextureData, "gnTextureDataFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnTextureCubeMapData, "gnTextureCubeMapDataFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateTexture, "gnCreateTextureFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyTexture, "gnDestroyTextureFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateUniformLayout, "gnCreateUniformLayoutFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyUniformLayout, "gnDestroyUniformLayoutFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateRenderPass, "gnCreateRenderPassFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyRenderPass, "gnDestroyRenderPassFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateFence, "gnCreateFenceFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnWaitForFence, "gnWaitForFenceFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnResetFence, "gnResetFenceFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyFence, "gnDestroyFenceFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateCommandBuffer, "gnCreateCommandBufferFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, _gnCreateCommandBuffers, "_gnCreateCommandBuffersFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBufferReset, "gnCommandBufferResetFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyCommandBuffer, "gnDestroyCommandBufferFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnBuildShaderModule, "gnBuildShaderModuleFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyShaderModule, "gnDestroyShaderModuleFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnBuildShader, "gnBuildShaderFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateUniform, "gnCreateUniformFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyUniform, "gnDestroyUniformFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnUpdateSamplerUniform, "gnUpdateSamplerUniformFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnUpdateBufferUniform, "gnUpdateBufferUniformFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnAPISupports, "gnAPISupportsFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetPrimative, "gnGraphicsPipelineSetPrimativeFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineEnableDynamicStates, "gnGraphicsPipelineEnableDynamicStatesFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineEnableDynamicState, "gnGraphicsPipelineEnableDynamicStateFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, _gnGraphicsPipelineSetViewport, "_gnGraphicsPipelineSetViewportFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetCrop, "gnGraphicsPipelineSetCropFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetDepthClamp, "gnGraphicsPipelineSetDepthClampFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetFillMode, "gnGraphicsPipelineSetFillModeFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetLineWidth, "gnGraphicsPipelineSetLineWidthFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetCullMode, "gnGraphicsPipelineSetCullModeFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetMultisampling, "gnGraphicsPipelineSetMultisamplingFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineEnableDepthTest, "gnGraphicsPipelineEnableDepthTestFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetColorBlend, "gnGraphicsPipelineSetColorBlendFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetVertexDescription, "gnGraphicsPipelineSetVertexDescriptionFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineBindShader, "gnGraphicsPipelineBindShaderFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetRenderPass, "gnGraphicsPipelineSetRenderPassFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineAddUniformLayout, "gnGraphicsPipelineAddUniformLayoutFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineAddPushConstant, "gnGraphicsPipelineAddPushConstantFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateGraphicsPipeline, "gnCreateGraphicsPipelineFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyGraphicsPipeline, "gnDestroyGraphicsPipelineFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateFramebuffer, "gnCreateFramebufferFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyFramebuffer, "gnDestroyFramebufferFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateFramebufferAttachment, "gnCreateFramebufferAttachmentFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCreateSyncSemaphore, "gnCreateSyncSemaphoreFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnDestroySyncSemaphore, "gnDestroySyncSemaphoreFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBufferStart, "gnCommandBufferStartFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBufferEnd, "gnCommandBufferEndFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBeginRenderPass, "gnCommandBeginRenderPassFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSetGraphicsPipeline, "gnCommandSetGraphicsPipelineFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBindSamplerUniform, "gnCommandBindSamplerUniformFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBindBuffer, "gnCommandBindBufferFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBindBufferUniform, "gnCommandBindBufferUniformFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandPushConstant, "gnCommandPushConstantFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandDrawIndexed, "gnCommandDrawIndexedFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSetViewport, "gnCommandSetViewportFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSetScissor, "gnCommandSetScissorFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, _gnCommandDraw, "gnCommandDrawFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandEndRenderPass, "gnCommandEndRenderPassFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSubmitGetValidPresentationQueue, "gnCommandSubmitGetValidPresentationQueueFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSubmit, "gnCommandSubmitFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandPresentGetValidPresentationQueue, "gnCommandPresentGetValidPresentationQueueFn");
//     // gnLoadDLLFunction(gnRenderingAPILIB, gnCommandPresent, "gnCommandPresentFn");

//     return GN_SUCCESS;
// }

// void* gnLoadFunction(gnString name) {
//     return gnLoadFunctionPtr(gnRenderingAPILIB, name);
// }

// void gnDestroy() {
//     gnUnloadDLL(&gnRenderingAPILIB);
// }
