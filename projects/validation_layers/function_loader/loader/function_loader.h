#pragma once
#include "loader/src/gryphn_instance_functions.h"
#include "loader/src/gryphn_device_functions.h"
#include "loader/src/gryphn_command_functions.h"

typedef struct gryphnInstanceFunctionLayers gryphnInstanceFunctionLayers;
gryphnInstanceFunctionLayers checkerLoadInstanceFunctions(void);

gnInstanceFunctions loadFunctionLoaderInstanceFunctions(void);
gnDeviceFunctions loadFunctionLoaderDeviceFunctions(void);
gnCommandFunctions loadFunctionLoaderCommandFunctions(void);

#include "extensions/synchronization/loader/sync_functions.h"
#include "extensions/queues/queues_functions.h"
gnSyncExtFunctions loadFunctionLoaderSyncExtFunctions(void);
gnQueueExtFunctions loadFunctionLoaderQueueExtFunctions(void);
