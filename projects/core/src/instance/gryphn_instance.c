#include "gryphn_instance.h"
#include "instance/gryphn_instance.h"
#include <loader/src/gryphn_instance_functions.h>
#include "loader/src/gryphn_extension_loader.h"
#include "loader/src/gryphn_loader.h"
#include "loader/src/gryphn_loader.h"

// this implementation of gnCreateInstance cannot return GN_UNLOADED_LAYER
gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceCreateInfo* info) {
    *instance = malloc(sizeof(struct gnInstance_t));
    (*instance)->hasDebugger = GN_FALSE;
    (*instance)->layers = loaderLayerArrayListCreate();
    loaderLayerArrayListAdd(&(*instance)->layers, loadLayer((loaderInfo){
        .api = info->coreAPI,
        .layerToLoad = api_layer
    }));

    gnBool unsupportedExtension = GN_FALSE;
    for (int c = 0; c < GN_EXT_MAX; c++) (*instance)->enabledExtensions[c] = GN_FALSE;
    for (int i = 0; i < info->extensionCount; i++) {
        (*instance)->enabledExtensions[info->extensions[i]] = GN_TRUE;
        if (!gnIsExtensionSuppoted(info->coreAPI, info->extensions[i])) unsupportedExtension = GN_TRUE;
    }

    if ((*instance)->enabledExtensions[GN_EXT_SYNCHRONIZATION]) (*instance)->layers.data[0].syncFunctions = loadAPISyncFunctions(info->coreAPI);
    if ((*instance)->enabledExtensions[GN_EXT_QUEUES]) (*instance)->layers.data[0].queueFunctions = loadAPIQueueFunctions(info->coreAPI);

    if (info->debuggerInfo.layerCount > 0) {
        for (int i = 0; i < info->debuggerInfo.layerCount; i++) {
            if (info->debuggerInfo.layers[i] == GN_DEBUGGER_LAYER_FUNCTIONS) {
                loaderLayerArrayListAdd(&(*instance)->layers, loadLayer((loaderInfo){
                    .api = info->coreAPI,
                    .layerToLoad = function_checker_layer
                }));
            }
        }
        (*instance)->debugger = info->debuggerInfo;
        (*instance)->hasDebugger = GN_TRUE;
    }

    (*instance)->currentLayer = ((*instance)->layers.count - 1);
    for (int i = 0; i < (*instance)->layers.count; i++) (*instance)->layers.data[i].layerIndex = i;
    (*instance)->callingLayer = &(*instance)->layers.data[(*instance)->layers.count - 1];
    gnReturnCode core_code = (*instance)->callingLayer->instanceFunctions._gnCreateInstance((*instance), info);
    if (unsupportedExtension) return GN_UNLOADED_EXTENSION;
    return core_code;
}

void gnDestroyInstance(gnInstanceHandle instance) {
    instance->callingLayer->instanceFunctions._gnDestroyInstance(instance);
}
