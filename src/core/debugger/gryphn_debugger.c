#include "gryphn_debugger.h"
#include <core/gryphn_platform_functions.h>
#include "stdio.h"

gnReturnCode gnCreateDebugger(gnDebugger* debugger, const struct gnDebuggerInfo_t info) {
    debugger->info = info;
    return GN_SUCCESS;
}
void gnDestroyDebugger(gnDebugger* debugger) {
    // debugger->instance->functions->_gnDestroyDebugger(debugger);
}
