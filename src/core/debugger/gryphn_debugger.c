#include "gryphn_debugger.h"
#include "core/gryphn_platform_functions.h"
#include "stdio.h"

gnReturnCode gnCreateDebugger(gnDebugger* debugger, gnInstance* instance, const struct gnDebuggerInfo_t info) {
    debugger->instance = instance;
    return instance->functions->_gnCreateDebugger(debugger, instance, info);
}
void gnDestroyDebugger(gnDebugger* debugger) {
    debugger->instance->functions->_gnDestroyDebugger(debugger);
}
