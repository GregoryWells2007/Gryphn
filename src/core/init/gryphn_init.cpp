#include <core/init/gryphn_init.h>
#include <dlfcn.h>
#include <platform/gryphn_platform_include.h>
#include <algorithm>
#include <gryphn/gryphn.h>

bool RenderingAPISupported(gnRenderingAPI api) {
    std::vector<gnRenderingAPI> supportedRenderingAPIS = gnGetSupportedRenderingAPIS();
    return std::find(supportedRenderingAPIS.begin(), supportedRenderingAPIS.end(), api) != supportedRenderingAPIS.end();
}

static void* gnRenderingAPILIB;

//#define LOAD_FUNC(dll, func) gnPlatformLoadDLLFunction(dll, func, gnString(#func) + "Fn")

#define gnLoadDLLFunction(dll, func, func_name) \
 gnPlatformLoadDLLFunction(dll, func, func_name); \
 if (func == nullptr) return gnReturnError(GN_FUNCTION_NOT_FOUND, gnString("GN_FUNC_(") + gnString(#func) + ")_NOT_LOADED")

gnReturnCode gnInit(gnRenderingAPI RenderingAPI) {
    gnString libName = "";

    switch (RenderingAPI) {
        case GN_RENDERINGAPI_NONE: {
            return gnReturnError(GN_UNSUPPORTED_RENDERING_API, "rendering api_none unsupported");
        }
        case GN_RENDERINGAPI_SOFTWARE: {
            return gnReturnError(GN_UNSUPPORTED_RENDERING_API, "rendering api_software unsupported");
        }
        case GN_RENDERINGAPI_OPENGL: {
            return gnReturnError(GN_UNSUPPORTED_RENDERING_API, "rendering api_opengl unsupported");
        }
        case GN_RENDERINGAPI_VULKAN: {
            if (!RenderingAPISupported(GN_RENDERINGAPI_VULKAN)) return gnReturnError(GN_UNSUPPORTED_RENDERING_API, "rendering api vulkan unsupported");
            libName = "GryphnVulkanImpl";
            break;
        }
        case GN_RENDERINGAPI_DIRECTX11: {
            return gnReturnError(GN_UNSUPPORTED_RENDERING_API, "rendering api directx11 unsupported");
        }
        case GN_RENDERINGAPI_DIRECTX12: {
            return gnReturnError(GN_UNSUPPORTED_RENDERING_API, "rendering api directx12 unsupported");
        }
        case GN_RENDERINGAPI_METAL: {
            if (!RenderingAPISupported(GN_RENDERINGAPI_METAL)) return gnReturnError(GN_UNSUPPORTED_RENDERING_API, "rendering api metal unsupported");
            libName = "GryphnMetalImpl";
            break;
        }
    }

    gnRenderingAPILIB = gnPlatformLoadDLL(gnString("gryphn/rendering_apis/") + libName);
    if (!gnRenderingAPILIB) { return gnReturnError(GN_UNABLE_TO_LOAD_DLL, "GN_ERROR_UNABLE_TO_LOAD_DLL"); }

    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateInstance, "gnCreateInstanceFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyInstance, "gnDestroyInstanceFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGetPlatformLayerName, "gnGetPlatformLayerNameFn");

    // LOAD THE SET WINDOW FUNCTIONS
    #ifdef GN_PLATFORM_LINUX
        #ifdef GN_WINDOW_X11
            gnLoadDLLFunction(gnRenderingAPILIB, gnCreateX11WindowSurface, "gnCreateX11WindowSurfaceFn");
        #endif
        #ifdef GN_WINDOW_WAYLAND
            gnLoadDLLFunction(gnRenderingAPILIB, gnCreateWaylandWindowSurface, "gnCreateWaylandWindowSurfaceFn");
        #endif
    #endif


    #ifdef GN_PLATFORM_WIN32
        gnLoadDLLFunction(gnRenderingAPILIB, gnCreateWindowsWindowSurface, "gnCreateWindowsWindowSurfaceFn");
    #endif

    #ifdef GN_PLATFORM_MACOS
        gnLoadDLLFunction(gnRenderingAPILIB, gnCreateMacOSWindowSurface, "gnCreateMacOSWindowSurfaceFn");
    #endif
    // This is stupid

    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateDebugger, "gnCreateDebuggerFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyDebugger, "gnDestroyDebuggerFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGetPhysicalOutputDevices, "gnGetPhysicalOutputDevicesFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDeviceSupportsAPI, "gnDeviceSupportsAPIFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnRegisterOutputDevice, "gnRegisterOutputDeviceFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnWaitForDevice, "gnWaitForDeviceFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyOutputDevice, "gnDestroyOutputDeviceFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGetDevicePresentationDetails, "gnGetDevicePresentationDetailsFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnPresentationQueueGetNextImageAsync, "gnPresentationQueueGetNextImageAsyncFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnPresentationQueueGetState, "gnPresentationQueueGetStateFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreatePresentationQueue, "gnCreatePresentationQueueFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyPresentationQueue, "gnDestroyPresentationQueueFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnVertexDescriptionSetBindingDescription, "gnVertexDescriptionSetBindingDescriptionFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnVertexDescriptionSetPropertiesCount, "gnVertexDescriptionSetPropertiesCountFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnVertexDescriptionSetProperty, "gnVertexDescriptionSetPropertyFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateBuffer, "gnCreateBufferFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnBufferData, "gnBufferDataFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnBufferMapData, "gnBufferMapDataFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyBuffer, "gnDestroyBufferFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnBufferSubData, "gnBufferSubDataFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnBufferClearData, "gnBufferClearDataFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnTextureData, "gnTextureDataFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnTextureCubeMapData, "gnTextureCubeMapDataFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateTexture, "gnCreateTextureFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyTexture, "gnDestroyTextureFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateUniformLayout, "gnCreateUniformLayoutFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyUniformLayout, "gnDestroyUniformLayoutFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateRenderPass, "gnCreateRenderPassFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyRenderPass, "gnDestroyRenderPassFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateFence, "gnCreateFenceFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnWaitForFence, "gnWaitForFenceFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnResetFence, "gnResetFenceFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyFence, "gnDestroyFenceFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateCommandBuffer, "gnCreateCommandBufferFn");
    gnLoadDLLFunction(gnRenderingAPILIB, _gnCreateCommandBuffers, "_gnCreateCommandBuffersFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBufferReset, "gnCommandBufferResetFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyCommandBuffer, "gnDestroyCommandBufferFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnBuildShaderModule, "gnBuildShaderModuleFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyShaderModule, "gnDestroyShaderModuleFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnBuildShader, "gnBuildShaderFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateUniform, "gnCreateUniformFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyUniform, "gnDestroyUniformFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnUpdateSamplerUniform, "gnUpdateSamplerUniformFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnUpdateBufferUniform, "gnUpdateBufferUniformFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnAPISupports, "gnAPISupportsFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetPrimative, "gnGraphicsPipelineSetPrimativeFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineEnableDynamicStates, "gnGraphicsPipelineEnableDynamicStatesFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineEnableDynamicState, "gnGraphicsPipelineEnableDynamicStateFn");
    gnLoadDLLFunction(gnRenderingAPILIB, _gnGraphicsPipelineSetViewport, "_gnGraphicsPipelineSetViewportFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetCrop, "gnGraphicsPipelineSetCropFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetDepthClamp, "gnGraphicsPipelineSetDepthClampFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetFillMode, "gnGraphicsPipelineSetFillModeFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetLineWidth, "gnGraphicsPipelineSetLineWidthFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetCullMode, "gnGraphicsPipelineSetCullModeFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetMultisampling, "gnGraphicsPipelineSetMultisamplingFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineEnableDepthTest, "gnGraphicsPipelineEnableDepthTestFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetColorBlend, "gnGraphicsPipelineSetColorBlendFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetVertexDescription, "gnGraphicsPipelineSetVertexDescriptionFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineBindShader, "gnGraphicsPipelineBindShaderFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineSetRenderPass, "gnGraphicsPipelineSetRenderPassFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineAddUniformLayout, "gnGraphicsPipelineAddUniformLayoutFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnGraphicsPipelineAddPushConstant, "gnGraphicsPipelineAddPushConstantFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateGraphicsPipeline, "gnCreateGraphicsPipelineFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyGraphicsPipeline, "gnDestroyGraphicsPipelineFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateFramebuffer, "gnCreateFramebufferFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroyFramebuffer, "gnDestroyFramebufferFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateFramebufferAttachment, "gnCreateFramebufferAttachmentFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCreateSyncSemaphore, "gnCreateSyncSemaphoreFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnDestroySyncSemaphore, "gnDestroySyncSemaphoreFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBufferStart, "gnCommandBufferStartFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBufferEnd, "gnCommandBufferEndFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBeginRenderPass, "gnCommandBeginRenderPassFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSetGraphicsPipeline, "gnCommandSetGraphicsPipelineFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBindSamplerUniform, "gnCommandBindSamplerUniformFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBindBuffer, "gnCommandBindBufferFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandBindBufferUniform, "gnCommandBindBufferUniformFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandPushConstant, "gnCommandPushConstantFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandDrawIndexed, "gnCommandDrawIndexedFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSetViewport, "gnCommandSetViewportFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSetScissor, "gnCommandSetScissorFn");
    gnLoadDLLFunction(gnRenderingAPILIB, _gnCommandDraw, "gnCommandDrawFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandEndRenderPass, "gnCommandEndRenderPassFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSubmitGetValidPresentationQueue, "gnCommandSubmitGetValidPresentationQueueFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandSubmit, "gnCommandSubmitFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandPresentGetValidPresentationQueue, "gnCommandPresentGetValidPresentationQueueFn");
    gnLoadDLLFunction(gnRenderingAPILIB, gnCommandPresent, "gnCommandPresentFn");


    // fucking hell I just realized that I do have to load in all the commands
    // I hate the way I chose to do this

    return GN_SUCCESS;
}

void gnDestroy() {
    dlclose(gnRenderingAPILIB);
}
