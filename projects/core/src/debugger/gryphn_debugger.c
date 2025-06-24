#include "gryphn_debugger.h"
#include <gryphn_platform_functions.h>

gnReturnCode gnCreateDebugger(gnDebuggerHandle* debugger, const gnDebuggerInfo info) {
    *debugger = malloc(sizeof(struct gnDebugger_t));
    (*debugger)->info = info;
    return GN_SUCCESS;
}
void gnDestroyDebugger(gnDebuggerHandle debugger) {}
