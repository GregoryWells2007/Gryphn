#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/gryphn_rendering_api.h"

struct gnPlatformInstance_t;
struct gnFunctions_t;
struct gnDynamicLibrary_t;
struct gnDebugger_t;

typedef struct gnInstanceInfo_t {
    gnString  applicationName;
    gnVersion applicationVersion;

    gnString  engineName;
    gnVersion engineVersion;

    gnRenderingAPI renderingAPI;
} gnInstanceInfo;

typedef struct gnInstance_t {
    struct gnPlatformInstance_t* instance;
    gnBool valid,
        loadDeviceFunctions,
        loadCommandFunctions;

    struct gnDynamicLibrary_t* dynamicLib;

    struct gnFunctions_t* functions;
    struct gnDeviceFunctions_t* deviceFunctions;
    struct gnCommandFunctions_t* commandFunctions;

    struct gnDebugger_t* debugger;
} gnInstance;

gnReturnCode gnCreateInstance(gnInstance* instance, struct gnInstanceInfo_t info);
void gnInstanceAttachDebugger(gnInstance* istance, struct gnDebugger_t* debugger);
void gnInstanceReleaseDebugger(gnInstance* instance);
void gnDestroyInstance(gnInstance* instance);
