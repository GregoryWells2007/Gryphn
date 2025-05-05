#include <core/debugger/gryphn_layers.h>

GN_EXPORT gnString gnGetPlatformLayerNameFn(const gnString& gnName) {
    if (gnStringEquals(gnName, "GN_DEFAULT_DEBUG_LAYER")) return "METAL_DEBUG_LAYER";
    return "GN_NO_LAYER";
}
