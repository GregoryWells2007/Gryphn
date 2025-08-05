#include "opengl_loader.h"
#include "gryphn_extensions.h"

gnBool openglIsExtensionSupported(gnExtension extension) {
    if (extension == GN_EXT_SYNCHRONIZATION) return GN_FALSE;
    if (extension == GN_EXT_QUEUES) return GN_FALSE;
    return GN_FALSE;
}
