#pragma once
#include "gryphn_rendering_api.h"
#include "gryphn_instance_functions.h"
#include "gryphn_device_functions.h"

typedef struct loaderInfo {
    gnRenderingAPI api;
} loaderInfo;

gnInstanceFunctions loadInstanceFunctions(loaderInfo info);
gnDeviceFunctions loadDeviceFunctions(loaderInfo info);
