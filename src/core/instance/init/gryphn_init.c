// #undef GN_UTILS_CPP
#include "gryphn_init.h"
#include <platform/gryphn_platform_include.h>
#include "gryphn_dynamic_library.h"
// #include <dlfcn.h>
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
}

void gnLoadDeviceFunctions(struct gnDynamicLibrary_t* lib, struct gnDeviceFunctions_t* functions) {

}
