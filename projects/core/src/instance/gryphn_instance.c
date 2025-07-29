#include "gryphn_instance.h"
#include "instance/gryphn_instance.h"
#include <loader/src/gryphn_instance_functions.h>
#include "loader/src/gryphn_loader.h"
#include "loader/src/gryphn_loader.h"

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceInfo info) {
    *instance = malloc(sizeof(struct gnInstance_t));
    (*instance)->hasDebugger = GN_FALSE;

    (*instance)->layers = loaderLayerArrayListCreate();
    loaderLayerArrayListAdd(&(*instance)->layers, loadLayer((loaderInfo){
        .api = info.renderingAPI,
        .layerToLoad = api_layer
    }));

    for (int c = 0; c < GN_EXT_MAX; c++) (*instance)->enabledExtensions[c] = GN_FALSE;
    for (int i = 0; i < info.extensionCount; i++) (*instance)->enabledExtensions[info.extensions[i]] = GN_TRUE;

    if ((*instance)->enabledExtensions[GN_EXT_SYNCHRONIZATION]) (*instance)->layers.data[0].syncFunctions = loadAPISyncFunctions(info.renderingAPI);

    gnBool loaderFunctionChecker = GN_FALSE;
    if (info.debugger != NULL) {
        for (int i = 0; i < info.debugger->layerCount; i++) {
            if (info.debugger->layers[i] == GN_DEBUGGER_LAYER_FUNCTIONS) loaderFunctionChecker = GN_TRUE;
        }
        (*instance)->debugger = *info.debugger;
        (*instance)->hasDebugger = GN_TRUE;
    }

    if (loaderFunctionChecker) {
        loaderLayerArrayListAdd(&(*instance)->layers, loadLayer((loaderInfo){
            .api = info.renderingAPI,
            .layerToLoad = function_checker_layer
        }));
    }

    (*instance)->currentLayer = ((*instance)->layers.count - 1);
    for (int i = 0; i < (*instance)->layers.count; i++) (*instance)->layers.data[i].layerIndex = i;

    // i hate this line of code but im not fixing it
    (*instance)->callingLayer = &(*instance)->layers.data[(*instance)->layers.count - 1];
    return (*instance)->callingLayer->instanceFunctions._gnCreateInstance((*instance), info);
}

void gnDestroyInstance(gnInstanceHandle instance) {
    instance->callingLayer->instanceFunctions._gnDestroyInstance(instance);
}
