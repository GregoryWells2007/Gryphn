#include <core/gryphn_support.h>

GN_EXPORT gnBool gnAPISupportsFn(gnFeature feature) {
    switch (feature) {
    case GN_DYNAMIC_STATES: return false; // from what I belive eveything is a dynamic state
    case GN_SYNC_OBJECTS: return true; // from what I belive metal does but i don't feel like supporting them
    }
    return false; // we should never get here
}
