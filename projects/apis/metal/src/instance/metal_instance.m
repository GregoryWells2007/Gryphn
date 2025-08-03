#include "metal_instance.h"

// metal instances are kinda useless
gnReturnCode metalCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, gryphnFunctionLayer* next) {
    if (instance->instance == NULL) instance->instance = malloc(sizeof(gnPlatformInstance));
    return GN_SUCCESS;
}
void metalDestroyInstance(gnInstanceHandle instance, gryphnFunctionLayer* next) {
    free(instance->instance);
}
