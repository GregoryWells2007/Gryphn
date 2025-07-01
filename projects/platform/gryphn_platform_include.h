#pragma once
#include <gryphn_rendering_api.h>

#ifdef GN_PLATFORM_LINUX
#include <platform_linux/gryphn_platform_linux.h>
#endif

#ifdef GN_PLATFORM_MACOS
#include <platform_macos/gryphn_platform_macos.h>
#endif

#ifdef GN_PLATFORM_WINDOWS
#include <platform_windows/gryphn_platform_windows.h>
#endif

gnRenderingAPI* gnGetSupportedRenderingAPIs(int* count);
gnBool gnSupportsRenderingAPI(gnRenderingAPI api);

// #ifdef __cplusplus
// template <typename function>
// void gnPlatformLoadDLLFunction(void *dll, function& func, gnString name) {
//     func = (function)gnLoadFunctionPtr(dll, name);
// }
// #endif
