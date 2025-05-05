#pragma once
#include <gryphn/gryphn_utils.h>

typedef enum gnFeature {
    GN_DYNAMIC_STATES, GN_SYNC_OBJECTS
} gnFeature;

inline gnBool (*gnAPISupports)(gnFeature feature);
