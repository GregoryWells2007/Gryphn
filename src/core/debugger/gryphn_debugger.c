#include "gryphn_debugger.h"
#include <core/gryphn_platform_functions.h>

gnReturnCode gnCreateDebugger(gnDebuggerHandle* debugger, const struct gnDebuggerInfo_t info) {
    *debugger = malloc(sizeof(struct gnDebugger_t));
    (*debugger)->info = info;
    return GN_SUCCESS;
}
void gnDestroyDebugger(gnDebuggerHandle debugger) {
    // free(debugger);
}
