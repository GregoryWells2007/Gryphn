#include <debugger/gryphn_debugger.h>

// these do nothing because I am too lazy to write a debugger for metal at this point in time
gnReturnCode gnCreateDebuggerFn(gnDebuggerHandle debugger, gnInstanceHandle instance, const gnDebuggerInfo info) {
    return GN_SUCCESS;
}
void gnDestroyDebuggerFn(gnDebuggerHandle instance) {

}
