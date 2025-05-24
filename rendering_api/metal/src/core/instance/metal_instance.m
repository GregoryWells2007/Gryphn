#include <gryphn/gryphn.h>
#include <gryphn/gryphn_utils.h>
#include "metal_instance.h"
// #include "bridge/metal_bridge.h"


gnReturnCode gnCreateInstanceFn(gnInstance* instance, gnInstanceInfo instanceInfo) {
    if (instance->instance == NULL) instance->instance = malloc(sizeof(gnPlatformInstance));
    return GN_SUCCESS;
}

void gnDestroyInstanceFn(gnInstance* instance) {
    free(instance->instance);
}
