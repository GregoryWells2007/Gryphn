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

    // (*instance)->functions =

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
    if (unsupportedExtension) return GN_UNLOADED_EXTENSION;
    return (*(PFN_gnCreateInstance*)(*instance)->functions.createInstance.function)(*instance, info, (*instance)->functions.createInstance.next);
}

void gnDestroyInstance(gnInstanceHandle* instance) {
    if (instance == GN_NULL_HANDLE) return;
    (*(PFN_gnDestroyInstance*)(*instance)->functions.destroyInstance.function)(*instance, (*instance)->functions.destroyInstance.next);
    *instance = GN_NULL_HANDLE;
}
