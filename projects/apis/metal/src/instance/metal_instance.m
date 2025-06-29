#include "metal_instance.h"

// metal instances are kinda useless
gnReturnCode createMetalInstance(gnInstanceHandle instance, gnInstanceInfo instanceInfo) {
    if (instance->instance == NULL) instance->instance = malloc(sizeof(gnPlatformInstance));
    return GN_SUCCESS;
}
void destroyMetalInstance(gnInstance instance) {
    free(instance->instance);
}
