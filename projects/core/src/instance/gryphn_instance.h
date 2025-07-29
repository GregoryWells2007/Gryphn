#pragma once
#include "core/src/gryphn_rendering_api.h"
#include "core/src/gryphn_handles.h"
#include "utils/gryphn_version.h"
#include "core/gryphn_error_code.h"
#include "core/src/instance/gryphn_debugger.h"
#include <gryphn_extensions.h>

typedef struct gnApplicationInfo {
    gnString  applicationName;
    gnVersion applicationVersion;

    gnString  engineName;
    gnVersion engineVersion;
} gnApplicationInfo;

typedef struct gnInstanceCreateInfo {
    gnApplicationInfo applicationInfo;
    gnDebuggerCreateInfo debuggerInfo;
    uint32_t extensionCount;
    gnExtension* extensions;
    gnRenderingAPI coreAPI;
} gnInstanceCreateInfo;

#ifdef GN_REVEAL_IMPL
#include <loader/src/gryphn_loader.h>
struct gnInstance_t {
    struct gnPlatformInstance_t* instance;
    loaderLayerArrayList layers;
    loaderLayer* callingLayer;
    uint32_t currentLayer;
    gnBool enabledExtensions[GN_EXT_MAX];
    gnBool hasDebugger;
    gnDebuggerCreateInfo debugger;
};
#endif

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceCreateInfo* info);
void gnDestroyInstance(gnInstanceHandle instance);
