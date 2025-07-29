#include "metal_loader.h"

gnBool metalIsExtensionSupported(gnExtension extension) {
    if (extension == GN_EXT_SYNCHRONIZATION) return GN_TRUE;
    if (extension == GN_EXT_QUEUES) return GN_FALSE;
    return GN_FALSE;
}
