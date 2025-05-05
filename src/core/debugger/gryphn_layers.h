#pragma once
#include <gryphn/gryphn_utils.h>

inline gnString (*gnGetPlatformLayerName)(const gnString& gnName);

#define GN_DEFAULT_DEBUG_LAYER gnGetPlatformLayerName("GN_DEFAULT_DEBUG_LAYER")
