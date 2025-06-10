#ifdef GN_PLATFORM_LINUX
#include "gryphn_platform_linux.h"
#include "core/gryphn_rendering_api.h"
#include "core/instance/init/gryphn_dynamic_library.h"
#include "dlfcn.h"

gnRenderingAPI renderingAPIs[2] = {
    GN_RENDERINGAPI_VULKAN,
    GN_RENDERINGAPI_SOFTWARE
};

gnRenderingAPI* gnGetSupportedRenderingAPIs(int* count) {
    *count = 2;
    return renderingAPIs;
}

struct gnDynamicLibrary_t* gnLoadDynamicLibrary(const gnString path) {
    struct gnDynamicLibrary_t* dll = malloc(sizeof(struct gnDynamicLibrary_t));
    dll->dllPtr = dlopen(gnToCString(gnCombineStrings(path, ".so")), RTLD_LAZY),
    dll->isValid = gnTrue;
    if (dll->dllPtr == NULL) dll->isValid = gnFalse;
    return dll;
}
void* gnLoadFunctionPtr(struct gnDynamicLibrary_t* dll, const char* name) {
    if (dll->isValid == gnFalse) return NULL;
    return dlsym(dll->dllPtr, name);
}
void gnUnloadDynamicLibrary(struct gnDynamicLibrary_t* dll) {
    if (dll->isValid) dlclose(dll->dllPtr);
}

#endif
