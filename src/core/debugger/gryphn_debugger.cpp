#include "gryphn_debugger.h"

void gnAddDebugLayer(gnDebugger& debugger, const gnString& layer) {
    gnListAdd(debugger.debug_layers, layer);
}

const gnList<gnString>& gnDebuggerGetDebugLayers(gnDebugger& debugger) {
    return debugger.debug_layers;
}
