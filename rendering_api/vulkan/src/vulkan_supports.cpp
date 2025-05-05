#include "core/gryphn_support.h"

GN_EXPORT gnBool gnAPISupportsFn(gnFeature feature) {
    if (feature == GN_DYNAMIC_STATES) return true;
    if (feature == GN_SYNC_OBJECTS) return true;
    return false;
}
