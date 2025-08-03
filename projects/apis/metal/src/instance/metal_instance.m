#include "metal_instance.h"

// metal instances are kinda useless
gnReturnCode metalCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, gryphnInstanceFunctionLayers* next) {
    if (instance->instance == NULL) instance->instance = malloc(sizeof(gnPlatformInstance));
    return GN_SUCCESS;
}
void metalDestroyInstance(gnInstanceHandle instance, gryphnInstanceFunctionLayers* next) {
    free(instance->instance);
}
