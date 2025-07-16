#pragma once
#include "core/src/gryphn_rendering_api.h"
#include "core/src/gryphn_handles.h"
#include "utils/gryphn_version.h"
#include "utils/gryphn_error_code.h"
#include "core/src/instance/gryphn_debugger.h"
#include <gryphn_extensions.h>

typedef struct gnInstanceInfo {
    gnString  applicationName;
    gnVersion applicationVersion;

    gnString  engineName;
    gnVersion engineVersion;

    gnRenderingAPI renderingAPI;
    gnDebuggerInfo* debugger;

    uint32_t extensionCount;
    gnExtension* extensions;
} gnInstanceInfo;

#ifdef GN_REVEAL_IMPL
#include <loader/src/gryphn_loader.h>
struct gnInstance_t {
    struct gnPlatformInstance_t* instance;
    gnBool valid;

    loaderLayerArrayList layers;
    loaderLayer* callingLayer;
    uint32_t currentLayer;

    gnBool enabledExtensions[GN_EXT_MAX];

    gnBool hasDebugger;
    gnDebuggerInfo debugger;
};
#endif

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceInfo info);
void gnDestroyInstance(gnInstanceHandle instance);
