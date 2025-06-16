#include "gryphn_instance.h"
#include "init/gryphn_init.h"
#include <core/gryphn_platform_functions.h>
#include "core/instance/gryphn_instance.h"
#include "stdio.h"

gnReturnCode gnCreateInstance(gnInstanceHandle* instanceHandlePtr, struct gnInstanceInfo_t info) {
    *instanceHandlePtr = malloc(sizeof(struct gnInstance_t));
    gnInstanceHandle instance = *instanceHandlePtr;
    instance->debugger = NULL;

    if (!gnIsAPISupported(info.renderingAPI)) return GN_UNSUPPORTED_RENDERING_API;
    instance->loadDeviceFunctions = gnFalse;
    instance->debugger = NULL;
    instance->dynamicLib = gnLoadRenderingDLL(info.renderingAPI);
    if (instance->dynamicLib == NULL) return GN_UNABLE_TO_LOAD_DYNAMIC_LIBARRY;
    instance->functions = malloc(sizeof(struct gnFunctions_t));
    instance->loadCommandFunctions = gnFalse;
    instance->loadDeviceFunctions = gnFalse;
    instance->debugger = info.debugger;
    gnLoadFunctions(instance->dynamicLib, instance->functions);
    return instance->functions->_gnCreateInstance(instance, info);
}

void gnDestroyInstance(gnInstanceHandle instance) {
    instance->functions->_gnDestroyInstance(instance);
}
