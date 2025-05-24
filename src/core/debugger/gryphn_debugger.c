#include "gryphn_debugger.h"
#include "core/gryphn_platform_functions.h"
#include "stdio.h"

gnReturnCode gnCreateDebugger(gnDebugger* debugger, gnInstance* instance, const struct gnDebuggerInfo_t info) {
    if (instance->debugger != NULL)
        return GN_DEBUGGER_EXISTS;
    debugger->info = info;
    debugger->instance = instance;
    instance->debugger = debugger;
    return instance->functions->_gnCreateDebugger(debugger, instance, info);
}
void gnDestroyDebugger(gnDebugger* debugger) {
    debugger->instance->functions->_gnDestroyDebugger(debugger);
}

void gnDebuggerSetErrorMessage(gnDebugger* debugger, gnMessageData data) {
    debugger->info.callback(
        GN_MESSAGE_ERROR,
        GN_DEBUG_MESSAGE_VALIDATION,
        data,
        debugger->info.userData
    );
}
