#include "gryphn_instance.h"
#include "init/gryphn_init.h"
#include <core/gryphn_platform_functions.h>
#include "core/debugger/gryphn_debugger.h"

gnReturnCode gnCreateInstance(gnInstanceHandle* instanceHandlePtr, struct gnInstanceInfo_t info) {
    *instanceHandlePtr = malloc(sizeof(struct gnInstance_t));
    gnInstanceHandle instance = *instanceHandlePtr;

    if (!gnIsAPISupported(info.renderingAPI)) return GN_UNSUPPORTED_RENDERING_API;
    instance->loadDeviceFunctions = gnFalse;
    instance->debugger = NULL;
    instance->dynamicLib = gnLoadRenderingDLL(info.renderingAPI);
    if (instance->dynamicLib == NULL) return GN_UNABLE_TO_LOAD_DYNAMIC_LIBARRY;
    instance->functions = malloc(sizeof(struct gnFunctions_t));
    gnLoadFunctions(instance->dynamicLib, instance->functions);
    return instance->functions->_gnCreateInstance(instance, info);
}
void gnInstanceAttachDebugger(gnInstanceHandle instance, struct gnDebugger_t *debugger) {
    if (instance->debugger != NULL) {
        gnDebuggerSetErrorMessage(debugger, (gnMessageData){
            .message = gnCreateString("Debugger already attached to instance")
        });
    }
    instance->debugger = debugger;
    debugger->instance = instance;
    gnReturnCode debuggerInfo = instance->functions->_gnCreateDebugger(debugger, instance, debugger->info);
    if (debuggerInfo != GN_SUCCESS) {
        gnDebuggerSetErrorMessage(debugger, (gnMessageData){
            .message = gnCreateString("Failed to attach debugger to instance")
        });
    }
}

#include "stdio.h"
void gnDestroyInstance(gnInstanceHandle instance) {
    if (instance->debugger) {
        instance->functions->_gnDestroyDebugger(instance->debugger);
    }
    instance->functions->_gnDestroyInstance(instance);
}

void gnInstanceReleaseDebugger(gnInstanceHandle instance) {
    instance->debugger = NULL;
}
