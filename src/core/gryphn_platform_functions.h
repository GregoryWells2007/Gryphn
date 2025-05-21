#pragma once
// theoretically you could have multible gryphn instances running in one application,
// why I dont know
#include "instance/gryphn_instance.h"
#include "debugger/gryphn_debugger.h"

typedef struct gnFunctions_t {
    gnReturnCode (*_gnCreateInstance)(gnInstance* instance, struct gnInstanceInfo_t info);
    void (*_gnDestroyInstance)(gnInstance* instance);

    gnReturnCode (*_gnCreateDebugger)(gnDebugger* debugger, gnInstance* instance, const struct gnDebuggerInfo_t info);
    void (*_gnDestroyDebugger)(gnDebugger* debugger);
} gnFunctions;
