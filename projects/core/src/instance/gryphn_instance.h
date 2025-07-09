#pragma once
#include "core/src/gryphn_rendering_api.h"
#include "core/src/gryphn_handles.h"
#include "utils/gryphn_version.h"
#include "utils/gryphn_error_code.h"
#include <loader/src/gryphn_loader.h>
#include <gryphn_extensions.h>

typedef struct gnInstanceInfo {
    gnString  applicationName;
    gnVersion applicationVersion;

    gnString  engineName;
    gnVersion engineVersion;

    gnRenderingAPI renderingAPI;
    gnDebuggerHandle debugger;

    uint32_t extensionCount;
    gnExtension* extensions;
} gnInstanceInfo;

#ifdef GN_REVEAL_IMPL
struct gnInstance_t {
    struct gnPlatformInstance_t* instance;
    gnBool valid;

    loaderLayerArrayList layers;
    loaderLayer* callingLayer;
    uint32_t currentLayer;

    gnDebuggerHandle debugger;
};
#endif

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceInfo info);
void gnDestroyInstance(gnInstanceHandle instance);
