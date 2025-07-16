#include "metal_loader.h"

gnBool metalIsExtensionSupported(gnExtension extension) {
    if (extension == GN_EXT_SYNCHRONIZATION) return gnTrue;
    if (extension == GN_EXT_QUEUES) return gnFalse;
    return gnFalse;
}
