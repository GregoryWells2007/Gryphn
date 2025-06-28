#pragma once
#include "stdint.h"
#include "utils/gryphn_string.h"
#include "utils/gryphn_error_code.h"
#include "gryphn_handles.h"

struct gnPlatformDebugger_t;

typedef enum gnMessageSeverity_e {
    GN_MESSAGE_VERBOSE = 0x00000001,
    GN_MESSAGE_INFO = 0x00000002,
    GN_MESSAGE_WARNING = 0x00000004,
    GN_MESSAGE_ERROR = 0x00000008,
} gnMessageSeverity;

typedef enum gnMessageType_e {
    GN_DEBUG_MESSAGE_GENERAL = 0x00000001,
    GN_DEBUG_MESSAGE_VALIDATION = 0x00000002,
    GN_DEBUG_MESSAGE_PERFORMANCE = 0x00000004,
} gnMessageType;

typedef struct gnMessageData {
    gnString message;
} gnMessageData;

typedef gnBool (*gnDebuggerCallback)(
    gnMessageSeverity messageSeverity,
    gnMessageType     messageType,
    gnMessageData     messageData,
    void*             userData);

typedef enum gnDebuggerLayer {
    GN_DEBUGGER_LAYER_PLATFORM, // enable platform (vulkan validation) layers
    GN_DEBUGGER_LAYER_FUNCTIONS // enable the checks on every function
} gnDebuggerLayer;

typedef struct gnDebuggerInfo {
    gnDebuggerCallback callback; // instance callback cannot be null
    void* userData;

    uint32_t layerCount;
    gnDebuggerLayer* layers;
} gnDebuggerInfo;

#ifdef GN_REVEAL_IMPL

struct gnDebugger_t {
    gnDebuggerInfo info;
};
#endif

gnReturnCode gnCreateDebugger(gnDebuggerHandle* debugger, const gnDebuggerInfo info);
void gnDestroyDebugger(gnDebuggerHandle debugger);

#ifdef GN_REVEAL_IMPL
static void gnDebuggerSetErrorMessage(gnDebuggerHandle debugger, gnMessageData data) {
    if (debugger == NULL) return;

    debugger->info.callback(
        GN_MESSAGE_ERROR,
        GN_DEBUG_MESSAGE_VALIDATION,
        data,
        debugger->info.userData
    );
}
#endif
