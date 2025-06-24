#include "gryphn_instance.h"
#include <gryphn_platform_functions.h>
#include "instance/gryphn_instance.h"
#include <loader/src/gryphn_instance_functions.h>
#include "loader/src/gryphn_loader.h"

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceInfo info) {
    *instance = malloc(sizeof(struct gnInstance_t));

    loaderInfo loadInfo = {
        .api = info.renderingAPI
    };

    (*instance)->instanceFunctions = loadInstanceFunctions(loadInfo);
    (*instance)->deviceFunctions = loadDeviceFunctions(loadInfo);
    (*instance)->debugger = info.debugger;
    return (*instance)->instanceFunctions._gnCreateInstance((*instance), info);
}

void gnDestroyInstance(gnInstanceHandle instance) {
    instance->instanceFunctions._gnDestroyInstance(instance);
}
