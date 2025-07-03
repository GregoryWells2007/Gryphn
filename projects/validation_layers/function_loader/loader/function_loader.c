#include "function_loader.h"
#include "src/instance_functions.h"
#include "src/device_functions.h"
#include "src/command_functions.h"

gnInstanceFunctions loadFunctionLoaderInstanceFunctions() {
    return (gnInstanceFunctions){
        ._gnCreateInstance = checkCreateInstance,
        ._gnDestroyInstance = checkDestroyInstance,

        ._gnGetPhysicalDevices = checkGetPhysicalDevices,
        ._gnQueueCanPresentToSurface = checkQueueCanPresentToSurface,

        ._gnCreateOutputDevice = checkCreateOutputDevice,
        ._gnDestroyOutputDevice = checkDestroyOutputDevice,


        #ifdef GN_PLATFORM_LINUX
            #ifdef GN_WINDOW_X11
                ._gnCreateX11WindowSurface = checkCreateX11WindowSurface,
            #endif
            #ifdef GN_WINDOW_WAYLAND
                ._gnCreateWaylandWindowSurface,
            #endif
        #endif


        #ifdef GN_PLATFORM_WIN32
            ._gnCreateWin32WindowSurface,
        #endif

        #ifdef GN_PLATFORM_MACOS
            ._gnCreateMacOSWindowSurface = checkCreateSurfaceMacOS,
        #endif

        ._gnDestroyWindowSurface = checkDestroyWindowSurface,
        ._gnGetSurfaceDetails = checkGetSurfaceDetails
    };
}
gnDeviceFunctions loadFunctionLoaderDeviceFunctions() {
    return (gnDeviceFunctions){
        ._gnCreatePresentationQueue = checkCreatePresentationQueue,
        ._gnPresentationQueueGetImage = checkPresentationQueueGetImage,
        ._gnDestroyPresentationQueue = checkDestroyPresentationQueue,

        ._gnCreateShaderModule = checkCreateShaderModule,
        ._gnDestroyShaderModule = checkDestroyShaderModule,

        ._gnCreateRenderPassDescriptor = checkCreateRenderPassDescriptor,
        ._gnDestroyRenderPassDescriptor = checkDestroyRenderPassDescriptor,

        ._gnCreateGraphicsPipeline = checkCreateGraphicsPipeline,
        ._gnDestroyGraphicsPipeline = checkDestroyGraphicsPipeline,

        ._gnCreateFramebuffer = checkCreateFramebuffer,
        ._gnDestroyFramebuffer = checkDestroyFramebuffer,

        ._gnCreateCommandPool = checkCreateCommandPool,
        ._gnDestroyCommandPool = checkDestroyCommandPool,

        ._gnCreateSemaphore = checkCreateSemaphore,
        ._gnDestroySemaphore = checkDestroySemaphore,

        ._gnCreateBuffer = checkCreateBuffer,
        ._gnBufferData = checkBufferData,
        ._gnBufferSubData = checkBufferSubData,
        ._gnMapBuffer = checkMapBuffer,
        ._gnDestroyBuffer = checkDestroyBuffer,

        ._gnCreateUniformPool = checkCreateUniformPool,
        ._gnUniformPoolAllocateUniforms = checkUniformPoolAllocateUniforms,
        ._gnDestroyUniformPool = checkDestroyUniformPool,

        ._gnUpdateBufferUniform = checkUpdateBufferUniform,
        ._gnUpdateStorageUniform = checkUpdateStorageUniform,
        ._gnUpdateImageUniform = checkUpdateImageUniform,

        ._gnCreateTexture = checkCreateTexture,
        ._gnTextureData = checkTextureData,
        ._gnDestroyTexture = checkDestroyTexture,

        ._gnCreateFence = checkCreateFence,
        ._gnWaitForFence = checkWaitForFence,
        ._gnResetFence = checkResetFence,
        ._gnDestroyFence = checkDestroyFence,

        ._gnSubmit = checkSubmit,
        ._gnPresent = checkPresent,

        ._gnWaitForDevice = checkWaitForDevice
    };
}
gnCommandFunctions loadFunctionLoaderCommandFunctions() {
    return (gnCommandFunctions){
        ._gnCommandPoolAllocateCommandBuffers = checkCommandPoolAllocateCommandBuffers,
        ._gnBeginCommandBuffer = checkBeginCommandBuffer,
        ._gnResetCommandBuffer = checkResetCommandBuffer,
        ._gnEndCommandBuffer = checkEndCommandBuffer,
        ._gnDestroyCommandBuffer = checkDestroyCommandBuffer,

        ._gnCommandBeginRenderPass = checkCommandBeginRenderPass,
        ._gnCommandEndRenderPass = checkCommandEndRenderPass,
        ._gnCommandBindGraphicsPipeline = checkCommandBindGraphicsPipeline,
        ._gnCommandSetViewport = checkCommandSetViewport,
        ._gnCommandSetScissor = checkCommandSetScissor,
        ._gnCommandBindUniform = checkCommandBindUniform,
        ._gnCommandPushConstant = checkCommandPushConstant,

        ._gnCommandBindBuffer = checkCommandBindBuffer,
        ._gnCommandDraw = checkCommandDraw,
        ._gnCommandDrawIndexed = checkCommandDrawIndexed,
    };
}
