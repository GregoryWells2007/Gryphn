#include "gryphn_instance.h"
#include <gryphn_platform_functions.h>
#include "instance/gryphn_instance.h"
#include "loader/src/gryphn_loader.h"

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceInfo info) {
    *instance = malloc(sizeof(struct gnInstance_t));
    // instance->dynamicLib = gnLoadRenderingDLL(info.renderingAPI);
    // if (instance->dynamicLib == NULL) return GN_UNABLE_TO_LOAD_DYNAMIC_LIBARRY;
    // instance->functions = gnLoadFunctions(instance);

    // if (info.debugger)
    //     instance->debugger = info.debugger;

    // return instance->functions->_gnCreateInstance(instance, info);
    return GN_SUCCESS;
}

void gnDestroyInstance(gnInstanceHandle instance) {
    instance->functions->_gnDestroyInstance(instance);
}
