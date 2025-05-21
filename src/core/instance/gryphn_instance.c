#include "gryphn_instance.h"
#include "init/gryphn_init.h"
#include <core/gryphn_platform_functions.h>

gnReturnCode gnCreateInstance(gnInstance* instance, struct gnInstanceInfo_t info) {
    if (!gnIsAPISupported(info.renderingAPI)) return GN_UNSUPPORTED_RENDERING_API;
    instance->dynamicLib = gnLoadRenderingDLL(info.renderingAPI);
    if (instance->dynamicLib == NULL) return GN_UNABLE_TO_LOAD_DYNAMIC_LIBARRY;
    instance->functions = malloc(sizeof(struct gnFunctions_t));
    gnLoadFunctions(instance->dynamicLib, instance->functions);

    return instance->functions->_gnCreateInstance(instance, info);
}
void gnDestroyInstance(gnInstance* instance) {
    instance->functions->_gnDestroyInstance(instance);
}
