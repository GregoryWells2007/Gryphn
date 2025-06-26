#pragma once
#include "gryphn_instance_functions.h"
#include "gryphn_device_functions.h"
#include "gryphn_command_functions.h"
#include "gryphn_loader_info.h"
#include "utils/lists/gryphn_array_list.h"

typedef struct loaderLayer {
    gnInstanceFunctions instanceFunctions;
    gnDeviceFunctions deviceFunctions;
    gnCommandFunctions commandFunctions;
} loaderLayer;

loaderLayer loadLayer(loaderInfo info);
GN_ARRAY_LIST(loaderLayer);
