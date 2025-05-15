#undef GN_UTILS_CPP
#include <core/debugger/gryphn_layers.h>

GN_EXPORT gnString gnGetPlatformLayerNameFn(const gnString& gnName) {
    if (gnStringEquals(gnName, "GN_DEFAULT_DEBUG_LAYER")) return gnCreateString("VK_LAYER_KHRONOS_validation");
    return gnCreateString("GN_NO_LAYER");
}
