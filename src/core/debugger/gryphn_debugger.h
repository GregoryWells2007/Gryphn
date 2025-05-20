#pragma once
#include "utils/strings/gryphn_string.h"
#include "utils/gryphn_error_code.h"

struct gnPlatformDebugger;

typedef struct gnDebuggerInfo_t {
    int layerCount;
    gnString* layerNames;
} gnDebuggerInfo;

typedef struct gnDebugger_t {
    struct gnPlatformDebugger* debugger;
} gnDebugger;

gnReturnCode gnCreateDebugger(gnDebugger* debugger, const struct gnDebuggerInfo_t info);
gnReturnCode gnDestroyDebugger(gnDebugger* debugger);
