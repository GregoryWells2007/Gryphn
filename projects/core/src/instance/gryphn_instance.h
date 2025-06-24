#pragma once
#include <gryphn/gryphn_utils.h>
#include "gryphn_rendering_api.h"
#include "gryphn_handles.h"

typedef struct gnInstanceFunctions gnInstanceFunctions;

typedef struct gnInstanceInfo_t {
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
    gnBool valid,
        loadDeviceFunctions,
        loadCommandFunctions;

    struct gnDynamicLibrary_t* dynamicLib;

    gnInstanceFunctions *functions, *unvalidatedFunctions;
    struct gnDeviceFunctions_t* deviceFunctions;
    struct gnCommandFunctions_t* commandFunctions;

    gnDebuggerHandle debugger;
};
#endif

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, struct gnInstanceInfo_t info);
void gnDestroyInstance(gnInstanceHandle instance);
