#include "metal_instance.h"

// metal instances are kinda useless
gnReturnCode metalCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, gryphnInstanceFunctionLayers* next) {
    if (next != NULL) return GN_SUCCESS;

    if (instanceInfo == NULL) return GN_INCOMPLETE;
    instance->instance = malloc(sizeof(gnPlatformInstance));
    return GN_SUCCESS;
}
void metalDestroyInstance(gnInstanceHandle instance, gryphnInstanceFunctionLayers* next) {
    if (next != NULL) return;
    free(instance->instance);
}
