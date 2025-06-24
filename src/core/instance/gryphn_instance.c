#include "gryphn_instance.h"
#include "init/gryphn_init.h"
#include <core/gryphn_platform_functions.h>
#include "core/instance/gryphn_instance.h"
#include "core/debugger/gryphn_debugger.h"
#include "core/gryphn_handles.h"
#include "stdio.h"
gnReturnCode gnCreateInstance(gnInstanceHandle* instanceHandlePtr, gnInstanceInfo info) {
    *instanceHandlePtr = malloc(sizeof(struct gnInstance_t));
    gnInstanceHandle instance = *instanceHandlePtr;
    if (!gnIsAPISupported(info.renderingAPI)) return GN_UNSUPPORTED_RENDERING_API;
    instance->loadDeviceFunctions = gnFalse;
    instance->dynamicLib = gnLoadRenderingDLL(info.renderingAPI);
    if (instance->dynamicLib == NULL) return GN_UNABLE_TO_LOAD_DYNAMIC_LIBARRY;
    instance->functions = gnLoadFunctions(instance);

    if (info.debugger)
        instance->debugger = info.debugger;

    instance->loadCommandFunctions = gnFalse;
    instance->loadDeviceFunctions = gnFalse;
    return instance->functions->_gnCreateInstance(instance, info);
}

void gnDestroyInstance(gnInstanceHandle instance) {
    instance->functions->_gnDestroyInstance(instance);
}
