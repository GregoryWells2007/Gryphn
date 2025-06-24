#include "gryphn_instance.h"
#include <gryphn_platform_functions.h>
#include "instance/gryphn_instance.h"
#include "gryphn_handles.h"

gnReturnCode gnCreateInstance(gnInstanceHandle* instanceHandlePtr, gnInstanceInfo info) {
    // *instanceHandlePtr = malloc(sizeof(struct gnInstance_t));
    // gnInstanceHandle instance = *instanceHandlePtr;
    // if (!gnIsAPISupported(info.renderingAPI)) return GN_UNSUPPORTED_RENDERING_API;
    // instance->loadDeviceFunctions = gnFalse;
    // instance->dynamicLib = gnLoadRenderingDLL(info.renderingAPI);
    // if (instance->dynamicLib == NULL) return GN_UNABLE_TO_LOAD_DYNAMIC_LIBARRY;
    // instance->functions = gnLoadFunctions(instance);

    // if (info.debugger)
    //     instance->debugger = info.debugger;

    // instance->loadCommandFunctions = gnFalse;
    // instance->loadDeviceFunctions = gnFalse;
    // return instance->functions->_gnCreateInstance(instance, info);
    return GN_SUCCESS;
}

void gnDestroyInstance(gnInstanceHandle instance) {
    instance->functions->_gnDestroyInstance(instance);
}
