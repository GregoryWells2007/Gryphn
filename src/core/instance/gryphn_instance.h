#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/gryphn_rendering_api.h"
#include "core/gryphn_handles.h"

struct gnPlatformInstance_t;
struct gnFunctions_t;
struct gnDynamicLibrary_t;

typedef struct gnInstanceInfo_t {
    gnString  applicationName;
    gnVersion applicationVersion;

    gnString  engineName;
    gnVersion engineVersion;

    gnRenderingAPI renderingAPI;
} gnInstanceInfo;

#ifdef GN_REVEAL_IMPL
struct gnInstance_t {
    struct gnPlatformInstance_t* instance;
    gnBool valid,
        loadDeviceFunctions,
        loadCommandFunctions;

    struct gnDynamicLibrary_t* dynamicLib;

    struct gnFunctions_t* functions;
    struct gnDeviceFunctions_t* deviceFunctions;
    struct gnCommandFunctions_t* commandFunctions;

    gnDebuggerHandle debugger;
};
#endif

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, struct gnInstanceInfo_t info);
void gnInstanceAttachDebugger(gnInstanceHandle istance, gnDebuggerHandle debugger);
void gnInstanceReleaseDebugger(gnInstanceHandle instance);
void gnDestroyInstance(gnInstanceHandle instance);
