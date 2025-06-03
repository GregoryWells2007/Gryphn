#pragma once
#include "utils/strings/gryphn_string.h"
#include "utils/gryphn_error_code.h"
#include "core/instance/gryphn_instance.h"

struct gnPlatformDebugger_t;

typedef enum gnMessageSeverity_e {
    GN_MESSAGE_VERBOSE = 0x00000001,
    GN_MESSAGE_INFO = 0x00000010,
    GN_MESSAGE_WARNING = 0x00000100,
    GN_MESSAGE_ERROR = 0x00001000,
} gnMessageSeverity;

typedef enum gnMessageType_e {
    GN_DEBUG_MESSAGE_GENERAL = 0x00000001,
    GN_DEBUG_MESSAGE_VALIDATION = 0x00000002,
    GN_DEBUG_MESSAGE_PERFORMANCE = 0x00000004,
    // GN_DEBUG_MESSAGE_ADDRESS_BINDING = 0x00000008, vulkan had this but imma leave it out
} gnMessageType;

typedef struct gnMessageData {
    // const char*                                  pMessageIdName;
    // int32_t                                      messageIdNumber;
    // uint32_t                                     queueLabelCount;
    // const VkDebugUtilsLabelEXT*                  pQueueLabels;
    // uint32_t                                     cmdBufLabelCount;
    // const VkDebugUtilsLabelEXT*                  pCmdBufLabels;
    // uint32_t                                     objectCount;
    // const VkDebugUtilsObjectNameInfoEXT*         pObjects;
    //
    // If i ever figure out what this shit does il add it
    gnString message;
} gnMessageData;

typedef gnBool (*gnDebuggerCallback)(
    gnMessageSeverity messageSeverity,
    gnMessageType     messageType,
    gnMessageData     messageData,
    void*             userData);

typedef struct gnDebuggerInfo_t {
    gnDebuggerCallback callback;
    void* userData;
} gnDebuggerInfo;

typedef struct gnDebugger_t {
    struct gnPlatformDebugger_t* debugger;
    struct gnDebuggerInfo_t info;
    gnInstanceHandle instance;
} gnDebugger;

gnReturnCode gnCreateDebugger(gnDebugger* debugger, const struct gnDebuggerInfo_t info);
void gnDestroyDebugger(gnDebugger* debugger);

static void gnDebuggerSetErrorMessage(gnDebugger* debugger, gnMessageData data) {
    debugger->info.callback(
        GN_MESSAGE_ERROR,
        GN_DEBUG_MESSAGE_VALIDATION,
        data,
        debugger->info.userData
    );
}
