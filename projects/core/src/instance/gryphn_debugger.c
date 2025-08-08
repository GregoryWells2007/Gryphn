#include "gryphn_debugger.h"

void gnDebuggerSetVerboseMessage(gnDebuggerCreateInfo* debugger, gnMessageData data) {
    debugger->callback(
        GN_MESSAGE_VERBOSE,
        GN_DEBUG_MESSAGE_GENERAL,
        data,
        debugger->userData
    );
}
