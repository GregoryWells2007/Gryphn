#include <core/debugger/gryphn_debugger.h>

// these do nothing because I am too lazy to write a debugger for metal at this point in time
GN_EXPORT gnReturnCode gnCreateDebuggerFn(gnDebugger* debugger, gnInstance* instance, const gnDebuggerInfo_t info) {
    return GN_SUCCESS;
}
GN_EXPORT void gnDestroyDebuggerFn(gnDebugger& instance) {

}
// I will at some point but if you have chosen the fate of writing this on a mac than you should really
// hate yourself
