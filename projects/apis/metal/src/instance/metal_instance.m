#include "metal_instance.h"

// metal instances are kinda useless
gnReturnCode metalCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, gryphnInstanceFunctionLayers* next, gnAllocators* allocators) {
    if (next != NULL) return GN_SUCCESS;

    if (instanceInfo == NULL) return GN_INCOMPLETE;
    instance->instance = allocators->malloc(sizeof(gnPlatformInstance), allocators->userData);
    return GN_SUCCESS;
}
void metalDestroyInstance(gnInstanceHandle instance, gryphnInstanceFunctionLayers* next, gnAllocators* allocators) {
    if (next != NULL) return;
    allocators->free(instance->instance, allocators->userData);
}
