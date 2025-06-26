#pragma once
#include "gryphn_rendering_api.h"
#include "gryphn_handles.h"
#include "utils/gryphn_version.h"
#include "utils/gryphn_error_code.h"
#include "loader/src/gryphn_loader.h"

typedef struct gnInstanceInfo {
    gnString  applicationName;
    gnVersion applicationVersion;

    gnString  engineName;
    gnVersion engineVersion;

    gnRenderingAPI renderingAPI;
    gnDebuggerHandle debugger;
} gnInstanceInfo;

#ifdef GN_REVEAL_IMPL
struct gnInstance_t {
    struct gnPlatformInstance_t* instance;
    gnBool valid;

    loaderLayerArrayList layers;
    loaderLayer* callingLayer;

    gnDebuggerHandle debugger;
};
#endif

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceInfo info);
void gnDestroyInstance(gnInstanceHandle instance);
