#include "gryphn_instance.h"
#include "instance/gryphn_instance.h"
#include <loader/src/gryphn_instance_functions.h>
#include "loader/src/gryphn_loader.h"

gnReturnCode gnCreateInstance(gnInstanceHandle* instance, gnInstanceInfo info) {
    *instance = malloc(sizeof(struct gnInstance_t));

    (*instance)->layers = loaderLayerArrayListCreate();

    loaderLayerArrayListAdd(&(*instance)->layers, loadLayer((loaderInfo){
        .api = info.renderingAPI,
        .layerToLoad = api_layer
    }));

    loaderLayerArrayListAdd(&(*instance)->layers, loadLayer((loaderInfo){
        .api = info.renderingAPI,
        .layerToLoad = function_checker_layer
    }));

    loaderLayerArrayListAdd(&(*instance)->layers, loadLayer((loaderInfo){
        .api = info.renderingAPI,
        .layerToLoad = function_checker_layer
    }));

    (*instance)->currentLayer = ((*instance)->layers.count - 1);
    for (int i = 0; i < (*instance)->layers.count; i++) (*instance)->layers.data[i].layerIndex = i;

    // i hate this line of code but im not fixing it
    (*instance)->callingLayer = &(*instance)->layers.data[(*instance)->layers.count - 1];
    (*instance)->debugger = info.debugger;
    return (*instance)->callingLayer->instanceFunctions._gnCreateInstance((*instance), info);
}

void gnDestroyInstance(gnInstanceHandle instance) {
    instance->callingLayer->instanceFunctions._gnDestroyInstance(instance);
}
