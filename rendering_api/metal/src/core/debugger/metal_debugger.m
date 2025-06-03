#include <core/debugger/gryphn_debugger.h>

// these do nothing because I am too lazy to write a debugger for metal at this point in time
gnReturnCode gnCreateDebuggerFn(gnDebugger* debugger, gnInstanceHandle instance, const struct gnDebuggerInfo_t info) {
    return GN_SUCCESS;
}
void gnDestroyDebuggerFn(gnDebugger* instance) {

}
