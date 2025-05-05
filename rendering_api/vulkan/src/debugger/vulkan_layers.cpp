#include "core/debugger/gryphn_layers.h"

GN_EXPORT gnString gnGetPlatformLayerNameFn(const gnString& gnName) {
    if (gnStringEquals(gnName, "GN_DEFAULT_DEBUG_LAYER")) return "VK_LAYER_KHRONOS_validation";
    return "GN_NO_LAYER";
}
