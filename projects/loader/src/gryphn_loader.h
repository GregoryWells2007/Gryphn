#pragma once
#include "gryphn_device_functions.h"
#include "gryphn_command_functions.h"
#include "gryphn_loader_info.h"
#include "utils/lists/gryphn_array_list.h"
#include <Dispatcher/dispatcher.h>

#include "extensions/synchronization/loader/sync_functions.h"
#include "extensions/queues/queues_functions.h"

typedef struct loaderLayer {
    // idk why I sperate these info different classes, I should really shove them in one bit class
    // they used to be loaded seperatly but I guess there not anymore
    // initlization is hard

    // gnInstanceFunctions instanceFunctions;

    gnDeviceFunctions deviceFunctions;
    gnCommandFunctions commandFunctions;

    gnSyncExtFunctions syncFunctions;
    gnQueueExtFunctions queueFunctions;

    // this index is not set by loadLayer, set by gnCreateInstance, also not used for now
    uint32_t layerIndex;
} loaderLayer;

loaderLayer loadLayer(loaderInfo info);
GN_ARRAY_LIST(loaderLayer);

loaderLayer* loaderGetNextLayer(gnInstance instance);
void resetLayer(gnInstance instance);

gnSyncExtFunctions loadAPISyncFunctions(gnRenderingAPI api);
gnQueueExtFunctions loadAPIQueueFunctions(gnRenderingAPI api);



dispatcher_bool loadAPIInstanceFunctions(dispatcher_layer* layer);
