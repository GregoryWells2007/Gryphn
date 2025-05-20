#ifdef GN_PLATFORM_MACOS
#undef GN_UTILS_CPP
#include "core/gryphn_rendering_api.h"
#include "core/instance/init/gryphn_dynamic_library.h"
#include "dlfcn.h"

gnRenderingAPI renderingAPIs[3] = {
    GN_RENDERINGAPI_METAL,
    GN_RENDERINGAPI_VULKAN,
    GN_RENDERINGAPI_SOFTWARE
};

gnRenderingAPI* gnGetSupportedRenderingAPIs(int* count) {
    *count = 3;
    return renderingAPIs;
}

struct gnDynamicLibrary_t* gnLoadDynamicLibrary(const gnString path) {
    struct gnDynamicLibrary_t* dll = malloc(sizeof(struct gnDynamicLibrary_t));
    dll->dllPtr = dlopen(gnToCString(gnCombineStrings(path, ".dylib")), RTLD_LAZY),
    dll->isValid = true
    if (dll->dllPtr == NULL) dll->isValid = false;
    return dll;
}
void* gnLoadFunctionPtr(struct gnDynamicLibrary_t* dll, const char* name) {
    if (dll->isValid == false) return NULL;
    return dlsym(dll->dllPtr, name);
}
void gnUnloadDynamicLibrary(struct gnDynamicLibrary_t* dll) {
    if (dll->isValid) dlclose(dll->dllPtr);
}

#endif
