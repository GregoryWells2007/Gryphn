#pragma once


#ifdef GN_PLATFORM_LINUX
#include <platform/platform_linux/gryphn_platform_linux.h>
#endif

#ifdef GN_PLATFORM_MACOS
#include <platform/platform_macos/gryphn_platform_macos.h>
#endif

#ifdef GN_PLATFORM_WINDOWS
#include <platform/platform_windows/gryphn_platform_windows.h>
#endif

#include <core/gryphn_rendering_api.h>

std::vector<gnRenderingAPI> gnGetSupportedRenderingAPIS();
void* gnPlatformLoadDLL(gnString name);
void* gnLoadFunctionPtr(void* dll, gnString name);

template <typename function>
void gnPlatformLoadDLLFunction(void *dll, function& func, gnString name) {
    func = (function)gnLoadFunctionPtr(dll, name);
}
