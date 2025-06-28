#pragma once
#include "gryphn_rendering_api.h"

typedef enum toLoadLayer {
    no_layer, api_layer, function_checker_layer
} toLoadLayer;

typedef struct loaderInfo {
    gnRenderingAPI api;
    toLoadLayer layerToLoad;
} loaderInfo;
