#pragma once
#include "core/src/gryphn_rendering_api.h"
#include "core/src/gryphn_handles.h"
#include "utils/gryphn_version.h"
#include "core/gryphn_return_code.h"
#include "core/src/instance/gryphn_debugger.h"
#include <gryphn_extensions.h>
#include "Dispatcher/dispatcher.h"

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
    gnDebuggerCreateInfo debugger;
    gnBool enabledExtensions[GN_EXT_MAX];

    loaderLayerArrayList layers;
    loaderLayer* callingLayer;
    uint32_t currentLayer;
    gnBool hasDebugger;
};
#endif

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceCreateInfo* info);
void gnDestroyInstance(gnInstanceHandle* instance);
