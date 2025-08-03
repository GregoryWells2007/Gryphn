#pragma once
#include "loader/src/gryphn_instance_functions.h"
#include "loader/src/gryphn_device_functions.h"
#include "loader/src/gryphn_command_functions.h"

typedef struct gryphnInstanceFunctionLayers gryphnInstanceFunctionLayers;
gryphnInstanceFunctionLayers checkerLoadInstanceFunctions();

gnInstanceFunctions loadFunctionLoaderInstanceFunctions();
gnDeviceFunctions loadFunctionLoaderDeviceFunctions();
gnCommandFunctions loadFunctionLoaderCommandFunctions();

#include "extensions/synchronization/loader/sync_functions.h"
#include "extensions/queues/queues_functions.h"
gnSyncExtFunctions loadFunctionLoaderSyncExtFunctions();
gnQueueExtFunctions loadFunctionLoaderQueueExtFunctions();
