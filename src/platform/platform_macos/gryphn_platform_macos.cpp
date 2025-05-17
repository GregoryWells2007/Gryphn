#ifdef GN_PLATFORM_MACOS
#include <platform/platform_macos/gryphn_platform_macos.h>
#include <dlfcn.h>

std::vector<gnRenderingAPI> gnGetSupportedRenderingAPIS() {
    return { GN_RENDERINGAPI_METAL, GN_RENDERINGAPI_VULKAN };
}

void* gnPlatformLoadDLL(gnString name) {
    return dlopen(gnToCString(name + ".dylib"), RTLD_LAZY);
}

void* gnLoadFunctionPtr(void *dll, gnString name) {
    return dlsym(dll, gnToCString(name));
}

#endif
