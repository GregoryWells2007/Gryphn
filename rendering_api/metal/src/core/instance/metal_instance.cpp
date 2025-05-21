#include <gryphn/gryphn.h>
#include <gryphn/gryphn_utils.h>
// #include "bridge/metal_bridge.h"
#include "metal_instance.h"

GN_EXPORT gnReturnCode gnCreateInstanceFn(gnInstance* instance) {
    if (instance->instance == nullptr) instance->instance = new gnPlatformInstance();
    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyInstanceFn(gnInstance& instance) {

}

GN_EXPORT gnReturnCode gnCreateMacOSWindowSurfaceFn(gnInstance& instance, NS::Window* window, NS::View* view) {
    if (instance.instance == nullptr) instance.instance = new gnPlatformInstance();
    instance.instance->metalContentView = view;
    return GN_SUCCESS;
}
