#undef GN_UTILS_CPP
#include "gryphn_debugger.h"

static gnReturnCode (*_gnCreateDebugger)(gnDebugger* debugger, const struct gnDebuggerInfo_t info);
static void (*_gnDestroyDebugger)(gnDebugger* debugger);

void gn_load_functions() {

}

// void gnAddDebugLayer(gnDebugger& debugger, const gnString& layer) {
//     gnListAdd(debugger.debug_layers, layer);
// }

// const gnList<gnString>& gnDebuggerGetDebugLayers(gnDebugger& debugger) {
//     return debugger.debug_layers;
// }
