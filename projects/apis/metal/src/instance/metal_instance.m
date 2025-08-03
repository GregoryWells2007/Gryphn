#include "metal_instance.h"

// metal instances are kinda useless
gnReturnCode metalCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, PFN_gnCreateInstance_layer* next) {
    if (instance->instance == NULL) instance->instance = malloc(sizeof(gnPlatformInstance));
    return GN_SUCCESS;
}
void metalDestroyInstance(gnInstanceHandle instance, PFN_gnDestroyInstance_layer* next) {
    free(instance->instance);
}
